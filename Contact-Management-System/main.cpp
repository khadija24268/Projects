
//=================================================================================
// Name         : DS Assignment#2 
// Author       : Khadija Khalid
// Version      : 1.0
// Date Created : 07-11-2022
// Date Modified: 
// Description  : Starter Code for Contact Management System using BST Tree in C++
//=================================================================================
#include<iostream>
#include<cstdlib>
#include<sstream>
#include "myvector.h"
#include "contact.h"
#include "contactbst.h"

//==========================================================
void listCommands()
{
	cout<<"----------------------------------"<<endl;
	cout<<"import <path>      :Import contacts from a CSV file"<<endl
		<<"export <path>      :Export contacts to a CSV file"<<endl
		<<"add                :Add a new contact"<<endl
		<<"edit <key>         :Update a contact's details"<<endl
		<<"remove <key>       :Delete a contact"<<endl
		<<"searchFor <key>    :Search for a contact"<<endl
		<<"markFav <key>      :Mark as favourite"<<endl
		<<"unmarkFav <key>    :Unmark as favourite"<<endl
		<<"printASC           :Print contacts in ascending order"<<endl
		<<"printDES           :Print contacts in descending order"<<endl
		<<"printFav           :Print all favourite contacts"<<endl
		<<"help               :Display the available commands"<<endl
		<<"exit               :Exit the program"<<endl;
}
//==========================================================

// to be completed with ALL the necessary method definitions

//==========================================================
int main(void)
{

	ContactBST contacts;
	//complete the main method
	
	string user_input;
	string command;
	string key;

	string newf, newl, newe, newp, newci, newco, newfav;
	bool fav;

	while(true)
	{
		try
		{
			listCommands();
			cout<<">";
			getline(cin,user_input);


			
			stringstream sstr(user_input);
			getline(sstr,command,' ');
			getline(sstr,key);
			
			Node* root = contacts.getRoot();
			
			
			//else if( command =="find" or command =="f")	cout<<key<<(myBST.findKey(root,stoi(key))==nullptr ? " not found":" found")<<endl;
			if( command =="add" or command=="a")	{ 
				cout<<"Please enter the details of the contact: "<<endl<<"First Name: ";
				cin>>newf;
				cout<<"Last Name: ";
				cin>>newl;
				cout<<"Email: ";
				cin>>newe;
				cout<<"Phone#: ";
				cin>>newp;
				cout<<"City: ";
				cin>>newci;
				cout<<"Country: ";
				cin>>newco;
				cout<<"Do you want to add the contact in your favourites (y/n) ? : ";
				cin>>newfav;
				cin.ignore(256, '\n');
				if (newfav == "y"){fav = true;}
				else if (newfav == "n"){fav = false;}
				else if (newfav != "y" && newfav != "n"){cout<<"Invalid Input! Kindly Enter 'y' or 'n' only"<<endl;continue;}

				string name = newf + " " + newl;


				Contact* data = new Contact(newf, newl, newe, newp, newci, newco, fav);


				contacts.add(root, name, data);
				cout<<"Contact Successfully added!"<<endl;
			} 
			else if( command =="remove" or command=="r")	{
				contacts.remove(root, key);
				cout<<"Contact is Successfully removed!"<<endl;
			}
			else if( command =="edit")	{
				contacts.update(root, key);
			}
			else if( command == "markFav"){
				contacts.markFav(key);
			}
			else if( command == "unmarkFav"){
				contacts.unmarkFav(key);
			}
			else if( command == "printFav"){contacts.printFav(root);}
			else if( command == "printASC"){contacts.printASC(root);}
			else if( command == "printDES"){contacts.printDES(root);}
			else if( command == "import"){cout<<contacts.importCSV(key)<<endl;}
			else if( command == "export"){cout<<contacts.exportCSV(root,key)<<endl;}
			else if( command == "help"){listCommands();}
			else if( command =="exit" or command =="quit" or command =="q") {break;}
			else cout<<"Invalid command !!!"<<endl;
		}
		catch(exception &ex)
		{
			cout<<ex.what()<<endl;
		}

	}
	return 0;


	return 0;
}