#include "contact.hpp"

     string lowerString(string s) // Function to convert all characters in lower case
        {
           for(int i=0;i<s.length();i++)
                {
                    s[i]=tolower(s[i]);
                }
                return s;
        }
        
    void add(vector <contact> &contact_book) // Function to add a new contact in our contact book.
    {
        cout<<"Enter the first name:\n";
        cin>>contact_book.back().first_name;
        
        cout<<"Enter the last name:\n";
        cin>>contact_book.back().last_name;
        
        cout<<"Enter the contact number:\n";
        cin>>contact_book.back().contact_no;
        
        
            for(int i=0;i<contact_book.back().contact_no.length();i++)
            {
                if(contact_book.back().contact_no[i]<'0' || contact_book.back().contact_no[i]>'9')
                {
                    cout<<"Invalid number\n";
                    break;
                }
            }
        cout<<endl;
        
        cout<<"Contact Added Successfully!!"<<endl<<endl;
    }
    
 void search_contact(vector <contact> &contact_book,string name) // Funtion to search the contact
    {
        int count=0; // this is used to maintain the number of contacts found
        
        // Now we are searching(linearly) in our contact in our contact book.
        for(int i=0;i<contact_book.size();i++)
        {
            string d_first=lowerString(contact_book[i].first_name);
            string d_last=lowerString(contact_book[i].last_name);
            
            int pos1=d_first.find(name);
            int pos2=d_last.find(name);
            int pos3=contact_book[i].contact_no.find(name);
            
            // if given name is found in either prefix of first name,last name or contact book then we are printing it
            if(d_first[0]==name[0] or d_last[0]==name[0] or contact_book[i].contact_no[0]==name[0])
            {
                if(pos1!=string::npos )
                {
                    cout<<contact_book[i].first_name<<" "<<contact_book[i].last_name<<": "<<contact_book[i].contact_no<<endl<<endl;
                    count++;
                    
                    //if the contact is found then we swap it with the contact before it in order to give it priority in search before the other elements.
                    if(pos1>0)
                    swap(contact_book[pos1],contact_book[pos1-1]);
                }
                else if(pos2!=string:: npos)
                {
                    cout<<contact_book[i].first_name<<" "<<contact_book[i].last_name<<": "<<contact_book[i].contact_no<<endl<<endl;
                    count++;
                    if(pos2>0)
                    swap(contact_book[pos2],contact_book[pos2-1]);
                }
                else if(pos3!=string::npos)
                {
                    cout<<contact_book[i].first_name<<" "<<contact_book[i].last_name<<": "<<contact_book[i].contact_no<<endl<<endl;
                    count++;
                    if(pos3>0)
                    swap(contact_book[pos3],contact_book[pos3-1]);
                }
       
                
                else if((d_first+" "+d_last).find(name)!=string::npos)
                {
                    cout<<contact_book[i].first_name<<" "<<contact_book[i].last_name<<": "<<contact_book[i].contact_no<<endl;
                    count++;
                }
            
            }
        }
        
         cout<<count<<" results found\n"<<endl;
    }

int main()
{
    contact new_contact;// creating a new contact
    phoneBook book;// using a vector to store the contact book.
    while(true)
    {
    string choice;
    cout << "1. Add Contact"<<endl<<"2. Search Contact"<<endl<<"3. exit"<<endl ;// asking user for choice to add,search or not do anything and simply exiting
    cin >> choice;
    
        if(choice=="1")// if choice is 1 we are calling our add function to add contact in the contact book.
        {
            book.contact_book.push_back(new_contact);
            add(book.contact_book);
        }
        else if(choice=="2")// if choice is 2 we are calling the search function to search for the contact in contact book
        {
             string contact_name;
             cout<<"Enter the name or number to be searched:\n";
             getline(cin>>ws,contact_name);
            for(int i=0;i<contact_name.length();i++)
            {
                if(contact_name[i]>='A' && contact_name[i]<='Z')
                    contact_name[i]=tolower(contact_name[i]);
                    
            }
            
            search_contact(book.contact_book,contact_name);
            
        }
        else if(choice=="3")
        {
            break;
        }
        
        else
           cout<<"Invalid input"<<endl;
           
    }
}
           
