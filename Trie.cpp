#include <bits/stdc++.h>
using namespace std;

/*
    Time Complexity = O(N * (W ^ 2))
    Space Complexity = O(N * W)
    
    Where N is the number of elements in the given array/list and W is the maximum length of a string.
*/

class TrieNode
{
public:
    
    //    Each Trie Node contains a static array 'children' where each alphabet points to a Trie Node.
    TrieNode *children[26];

    //    'isEnd' is true if the node represents end of a contact.
    bool isEnd;

    //    Constructor
    TrieNode()
    {
        
        //    Initialize all the Trie nodes with NULL
        for (char i = 'a'; i <= 'z'; i++)
        {
            children[i - 'a'] = NULL;
        }

        isEnd = false;
    }
    ~TrieNode()
    {
        for (int i = 0; i < 26; i++)
        {
            if (children[i] != NULL)
            {
                delete children[i];
            }
        }
    }
};

void insertContact(string &str, TrieNode *root)
{
    int n = str.length();

    //    'itr' is used to iterate the Trie Nodes
    TrieNode *itr = root;

    for (int i = 0; i < n; i++)
    {
        
        //    Check if the str[i] is already present in our Trie.

        TrieNode *next = itr->children[str[i] - 'a'];

        if (next == NULL)
        {
            
            //   If not found then create a new TrieNode
            next = new TrieNode();

            //    Insert into the array.
            itr->children[str[i] - 'a'] = next;
        }

        //    Move the iterator('itr') to point to next Trie Node.
        itr = next;

        //    If its the last character of the string 'str' then mark 'isEnd' as true
        if (i == n - 1)
        {
            itr->isEnd = true;
        }
    }
}

void viewSuggestionsHelper(TrieNode *curr, string prefix, vector<string> &temp)
{
    
    //    Check if the string 'prefix' ends at this Node If yes then display the string found so far
    if (curr->isEnd)
    {
        temp.push_back(prefix);
    }

    //    Find all the adjacent Nodes to the current Node and then call the function recursively.
    for (char c = 'a'; c <= 'z'; c++)
    {
        TrieNode *next = curr->children[c - 'a'];

        if (next != NULL)
        {
            prefix.push_back(c);
            viewSuggestionsHelper(next, prefix, temp);
            prefix.pop_back();
        }
    }
}

vector<vector<string>> viewSuggestions(string &str, TrieNode *root)
{
    TrieNode *prev = root;

    string prefix = "";

    int n = str.length();

    vector<vector<string>> result;

    for (int i = 0; i < n; i++)
    {
        
        //    'prefix' stores the string formed so far.
        prefix.push_back(str[i]);

        //    Get the last character entered.
        char lastCharacter = prefix[i];

        //    Find the Node corresponding to the last character of 'prefix' which is pointed by prev of the Trie.
        TrieNode *curr = prev->children[lastCharacter - 'a'];

        //    If nothing found, then break the loop as no more prefixes are going to be present.
        if (curr == NULL)
        {
            i++;
            break;
        }

        //    If present in trie then insert all the contacts with given prefix in the result.
        vector<string> temp;

        viewSuggestionsHelper(curr, prefix, temp);

        result.push_back(temp);

        temp.clear();

        //    Change prev for next prefix
        prev = curr;
    }

    delete root;

    return result;
}

void insertContactList(vector<string> &contactList, TrieNode *root)
{

    int n = contactList.size();

    //    Insert each contact into the trie.
    for (int i = 0; i < n; i++)
    {
        insertContact(contactList[i], root);
    }
}

vector<vector<string>> phoneDirectory(vector<string> &contactList, string &queryStr)
{
    TrieNode *root = new TrieNode();

    //    Insert all the Contacts into Trie.
    insertContactList(contactList, root);

    //    Return the corresponding suggestions.
    return viewSuggestions(queryStr, root);
}

int main(){

    vector<string> contactList;
    string queryStr;
    int n;cin>>n;

    for(int i=0;i<n;i++){
        string contact ;
        cin>> contact;

        contactList.push_back(contact);
    }
    cin>>queryStr;
    vector<vector<string>> ans=phoneDirectory(contactList,queryStr);
   
    for(int i=0;i<ans.size();i++){
        for(int j=0;j<ans[i].size();j++){
            cout<<ans[i][j]<<" ";
        }
        cout<<endl;
    }
    cout<<endl;
}
