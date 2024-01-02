#include <iostream>
#include<string>
#include<fstream>
#include<exception>
#include<sstream>
#include<iomanip>
#include "contactbst.h"

ContactBST::ContactBST()
{
	//todo
	
	this->root = nullptr;
	MyVector<Contact*> contactVector;	

}

ContactBST::~ContactBST()
{
	//todo
	while(this->root != nullptr){
		remove (root, root->key);
	}

}

Node* ContactBST::getRoot()
{
	//todo
	
	return this->root;
}

void ContactBST::add(Node* ptr,string key, Contact *data)
{
	//todo

	if(this->root == nullptr){ //checks if the tree is empty 
		Node* newnode = new Node(key, data); //if tree empty, then new node created which is equal to the root
		root = newnode;
		root->left = nullptr; //left, right and parent attributes of root declared
		root->right = nullptr;
		root->parent = nullptr;

	}
	else{
		if(ptr->key == key){  //if a node with the same key (first and last name) found, then add the data of the new contact in the vector of the same ndode 
			ptr->contactVector.push_back(data);
		}
		if(key<ptr->key){
			if (ptr->left == nullptr){ //in the case of an empty left child when key is smaller than a node, creates a new node 
				Node* newkey = new Node(key, data);
				newkey->parent = ptr;
				ptr->left = newkey;
			}
			else{
				add(ptr->left, key, data); //otherwise calls the function recursively to the left to get to the base cases
			}
		}
		if(key>ptr->key){
			if (ptr->right == nullptr){ //in the case of an empty right child when key is bigger than a node, creates a new node
				Node* newkey = new Node(key, data);
				newkey->parent = ptr;
				ptr->right = newkey;
			}
			else{
				add(ptr->right, key, data); //otherwise calls the function recursively to the right to get to the base cases
			}
		}
	}
}


Node* ContactBST::findMin(Node *ptr)
{
	//iteratively goes to the left most node as that is the smallest
	if(ptr == NULL){
		return nullptr;
	}
	else{
		while(ptr->left!=nullptr){
			ptr= ptr->left;
		}
		return ptr;
	}
}
Node* ContactBST::findMax(Node *ptr)
{
	////iteratively goes to the right most node as that is the largest
	if(ptr== NULL){
		return nullptr;
	}
	else{
		while(ptr->right != nullptr){
			ptr = ptr->right;
		}
		return ptr;
	}
}


Node* ContactBST::searchFor(Node *ptr,string key)
{
	//if node doesnt exist
	if(ptr == nullptr){
		cout<<"Not found"<<endl;
		return nullptr;
	}
	//if it exists we simply return it (base case)
	if(ptr->key == key){
		return ptr;
	}
	
	else if(key<ptr->key){ //recursively call to the left if key smaller
		return searchFor(ptr->left, key);
	}
	else if (key>ptr->key){ //recursively call to the right if key bigger
		return searchFor(ptr->right, key);
	}
	else {return nullptr;}
	
}
//=========================================================
//Remove recursively the node with key value from the tree/subtree rooted at ptr
void ContactBST::remove(Node *root_ptr,string key)
{
	//if tree emoty, root is null and so returns message
	if(root_ptr== NULL){
		cout<<"Contact list is empty"<<endl;
	}
	else{
		Node* ptr = searchFor(root_ptr, key); //finds a pointer to the node 
		if(ptr == nullptr){ //if node doesnt exist, return the message
			cout<<"Contact does not exist"<<endl;
		}
		else{
			
			if (ptr->contactVector.size() == 1){ //incase when the node has contact data of only one contact
				if (ptr->left == nullptr && ptr->right == nullptr){ //checks if external node
					if (ptr->parent == nullptr){ //checks if root
						ptr= nullptr; //incase of a single root tree, removes root
						root = ptr;
						delete ptr;
					}
					else { //otherwise node is a leaf
						if (ptr == ptr->parent->left){
							ptr->parent->left = nullptr; //if it is left of its parent then parent's left is changed to null and node deleted
						}else{
							ptr->parent->right = nullptr; //if it is right of its parent then parent's right is changed to null and node deleted
						}
						delete ptr;
					}
				}
				else if(ptr->left != nullptr && ptr->right == nullptr){ //if left child exists 
					if(ptr->parent!=nullptr){ //if node is not root
						Node* child = ptr->left; //create a new node that connects node's child to node's parent and deletes node
						Node* grandpar = ptr->parent;
						if(ptr == grandpar->right){grandpar->right = child;}
						else{grandpar->left = child;}
						child->parent = grandpar;
						delete ptr;
					}
					else{ //otherwise find the maximum from the left side 
						Node* newnode = findMax(ptr->left);  //create a newnode with it 
						ptr->key = newnode->key; //assign max value from left side to node
						ptr->contactVector = newnode->contactVector;
						remove(newnode, newnode->key); //delete maxnode from left
					}
					

				}
				else if(ptr->right != nullptr && ptr->left == nullptr){ //if right child exists
					if (ptr->parent!=nullptr){//if node is not root
						Node* child = ptr->right; //create a new node that connects node's child to node's parent and deletes node
						Node* grandpar = ptr->parent;
						if(ptr == grandpar->right){grandpar->right = child;}
						else{grandpar->left = child;}
						child->parent = grandpar;
						delete ptr;
					}
					else{ //otherwise find the minimum from the left side
						Node* newnode = findMin(ptr->right); //create a newnode with it 
						ptr->key = newnode->key;//assign min value from left side to node
						ptr->contactVector = newnode->contactVector;
						remove(newnode, newnode->key);//delete minnode from left
					}

				}
				else if(ptr->right != nullptr && ptr->left != nullptr){ //if both children exist, we find max from the left side and make it the node and delete maxnode
					Node* newnode = findMax(ptr->left);
					ptr->key = newnode->key;
					ptr->contactVector = newnode->contactVector;
					remove(newnode, newnode->key);
				} 
			}
			else if (ptr->contactVector.size()>1){ //if node has data of more than one contact in its vector 
				char input;
				
				cout<<ptr->contactVector.size()<<" records found:"<<endl; //ask for input about contact
				//display
				for(int i=0; i<ptr->contactVector.size(); i++)
				{
					Contact *ct = ptr->contactVector.at(i);
					cout<<" "<<i+1<<". "<<ct->fname<<","<<ct->lname<<","<<ct->email<<","<<ct->primaryPhone<<","<<ct->city<<","<<ct->country<<","<<ct->isFav<<endl;
				}
				while(true){//while loop for error check in input 

				
					cout<<"Please select the record you want to update: ";
					cin>>input;

					cin.ignore(256, '\n');


					if (int(input) > 47 && int(input) < 58 && int(input)-48!=0 && int(input)-48<ptr->contactVector.size()+1){ //if input in the right range or an integer
						ptr->contactVector.erase((int(input)-48)-1); //simply call vector erase to delete contact from vector
						break;
					}
					else{
						cout<<"Invalid Input!"<<endl; //give error if wrong input
					}
				}

				

			}
			
		}

		
		
	}
	
	


}
void ContactBST::update(Node* root_ptr, string key)
{
	if(root_ptr== NULL){ //if tree empty
		cout<<"Tree is empty"<<endl;
	}
	else {
		Node* ptr = searchFor(root_ptr, key);
		if(ptr == nullptr){ 
			cout<<"Contact does not exist"<<endl; //if node doesnt exist
		}
		else{
			
				char contact_no; 
				char option;
				string newf, newl, newe , newp, newci, newco;
				string edit;
				
				cout<<ptr->contactVector.size()<<" records found:"<<endl;
				for(int i=0; i<ptr->contactVector.size(); i++)
				{
					Contact *ct = ptr->contactVector.at(i);
					cout<<" "<<i+1<<". "<<ct->fname<<","<<ct->lname<<","<<ct->email<<","<<ct->primaryPhone<<","<<ct->city<<","<<ct->country<<","<<ct->isFav<<endl;
				}
				// cout<<"Please select the record you want to update: ";
				// cin>>contact_no;
				// cin.ignore(256, '\n');

				while(true){
					//to check user input if it is an integer and within range of the records mentioned
				
					cout<<"Please select the record you want to update: ";
					cin>>contact_no;
					cin.ignore(256, '\n');


					if (int(contact_no) > 47 && int(contact_no) < 58 && int(contact_no)-48!=0 && int(contact_no)-48<ptr->contactVector.size()+1){

						break;
					}
					else{
						cout<<"Invalid Input!"<<endl;
					}
				}
				Contact *ct = ptr->contactVector.at(int(contact_no)-48-1); //points to the contact chosen by user

				bool exit = false;

				while(exit == false){
					cout<<"Which field do you want to edit? 1) First name , 2) Last Name , 3) Email , 4) Phone# , 5) City or 6) Country : ";
					cin>>option;
					cin.ignore(256, '\n');

					if (int(option) < 49 || int(option) > 54){
						continue;
					}

					//changes the rspective values of the contact
					if(int(option)-48 == 1){
						cout<<"Please enter the new First Name: ";
						cin>>newf;
						cin.ignore(256, '\n');
						ct->fname = newf;
					}
					else if(int(option)-48 == 2){
						cout<<"Please enter the new Last Name: ";
						cin>>newl;
						cin.ignore(256, '\n');
						ct->lname = newl;
					}
					else if(int(option)-48 == 3){
						cout<<"Please enter the new Email: ";
						cin>>newe;
						cin.ignore(256, '\n');
						ct->email = newe;
					}
					else if(int(option)-48 == 4){
						cout<<"Please enter the new Phone Number: ";
						cin>>newp;
						cin.ignore(256, '\n');
						ct->primaryPhone = newp;
					}
					else if(int(option)-48 == 5){
						cout<<"Please enter the new City: ";
						cin>>newci;
						cin.ignore(256, '\n');
						ct->city = newci;
					}
					else if(int(option)-48 == 6){
						cout<<"Please enter the new Country: ";
						cin>>newco;
						cin.ignore(256, '\n');
						ct->country = newco;
					}
					
					while (true){ //checks if user input correct otherwise asks again
						cout<<"Do you want to edit another field (y/n) ? : ";
						cin>>edit;
						cin.ignore(256, '\n');
						if(edit=="y" || edit== "n"){
							break;
						}
						else{
							cout<<"Invalid Input!"<<endl;
							continue;
						}
					}
					//continues loop if user says yes to changes 
					if(edit == "y"){
						continue;
					}
					else if(edit == "n"){
						exit = true;
						break;
					}
				}

				

			
		}
	}
}

void ContactBST::printASC(Node* ptr)
{

	if (ptr != nullptr)
	{
		//goes far left to the smallest node and prints the far left
		if (ptr->left != nullptr){

			printASC(ptr->left);
		}
		
			for(int i=0; i<ptr->contactVector.size(); i++)
			{
				Contact *ct = ptr->contactVector.at(i);
				cout<<ct->fname<<","<<ct->lname<<","<<ct->email<<","<<ct->primaryPhone<<","<<ct->city<<","<<ct->country<<","<<ct->isFav<<endl;
			}	
		//then moves to the right and recursively continues traversing from left to right
		if (ptr->right != nullptr){
			printASC(ptr->right);
		}
	
	}
	else{
		cout<<"No contacts Available"<<endl;
	}
}

void ContactBST::printDES(Node* ptr)
{
	if (ptr != nullptr)
	{
		//goes far right to the biggest node and prints the far right
		if (ptr->right != nullptr){

			printDES(ptr->right);
		}
		for(int i=0; i<ptr->contactVector.size(); i++)
			{
				Contact *ct = ptr->contactVector.at(i);
				cout<<ct->fname<<","<<ct->lname<<","<<ct->email<<","<<ct->primaryPhone<<","<<ct->city<<","<<ct->country<<","<<ct->isFav<<endl;
			}
		//then moves to the left and recursively continues traversing from right to left	
		if (ptr->left != nullptr){
			printDES(ptr->left);
		}
	}
	else{
		cout<<"No contacts Available"<<endl;
	}
}

bool ContactBST::markFav(string key)
{

	Node* ptr = searchFor(this->root, key); //calls search function to create a pointer to the node 

	if(ptr == nullptr){ //if contact doesnt exist, gives message 
		cout<<"Contact does not exist"<<endl;
		return 0;
	}

	else {
		char option;
		ptr->print();
		while(true){ //while loop to check the user input

				
			cout<<"Please select the record you want to update: ";
			cin>>option;

			cin.ignore(256, '\n');


			if (int(option) > 47 && int(option) < 58 && int(option)-48!=0 && int(option)-48<ptr->contactVector.size()+1){
				Contact *ct = ptr->contactVector.at((int(option)-48)-1);
				ct->isFav = true; //changes the isFav value from the contact class stored in vector 
				cout<<key<<"("<<ct->email<<") has been successfully marked as favourite!"<<endl;
				return 1;
				break;
			}
			else{
				cout<<"Invalid Input!"<<endl; 
				return 0;
			}
		}
		
	}
}

bool ContactBST::unmarkFav(string key){
	Node* ptr = searchFor(this->root, key); //calls search function to create a pointer to the node 

	if(ptr == nullptr){
		cout<<"Contact does not exist"<<endl; //if contact doesnt exist, gives message 
		return 0;
	}

	else {
		int option;
		ptr->print();
		while(true){ //while loop to check the user input

				
			cout<<"Please select the record you want to update: ";
			cin>>option;

			cin.ignore(256, '\n');


			if (int(option) > 47 && int(option) < 58 && int(option)-48!=0 && int(option)-48<ptr->contactVector.size()+1){
				Contact *ct = ptr->contactVector.at((int(option)-48)-1);
				ct->isFav = false; //changes the isFav value from the contact class stored in vector
				cout<<key<<"("<<ct->email<<") has been successfully unmarked as favourite!"<<endl;
				return 1;
				break;
			}
			else{
				cout<<"Invalid Input!"<<endl;
				return 0;
			}
		}
		
	}
}

void ContactBST::printFav(Node* ptr)
{
	//goes in order from left to right 
	if (ptr != nullptr)
	{
		
		if (ptr->left != nullptr){

			printFav(ptr->left);
		}//goes extreme left to the smallest node
		
			for(int i=0; i<ptr->contactVector.size(); i++)
			{
				Contact *ct = ptr->contactVector.at(i);
				if(ct->isFav == true){ //prints the contacts with the isFav value being equal to "1" meaning marked favourite 
					cout<<ct->fname<<","<<ct->lname<<","<<ct->email<<","<<ct->primaryPhone<<","<<ct->city<<","<<ct->country<<","<<ct->isFav<<endl;
				}
			}	
		//then moves from left to right
		if (ptr->right != nullptr){
			printFav(ptr->right);
		}
	
	}
	else{
		cout<<"No contacts Available"<<endl;
	}
}

int ContactBST::importCSV(string path)
{
	string line, first, last, email, phone, city, country, fav;
	ifstream fptr(path); //opens the file 
	int num=0;
	while(getline(fptr,line)){
		stringstream s(line); //stores the line in string s 
		getline(s, first, ','); //one by one stores the different values in the respective variables 
		getline(s, last, ',');
		getline(s, email, ',');
		getline(s, phone, ',');
		getline(s, city, ',');
		getline(s, country, ',');
		getline(s, fav, ',');
		bool isFav;
		if (fav == "1"){isFav = true;}
		else if (fav == "0"){isFav = false;}
		Contact* data = new Contact(first, last, email, phone, city, country, isFav);
		string key;
		key = first+" "+last;
		add(this->root, key, data); //calls add function to add the contacts
		num++;

	}
	fptr.close();
	return num;
} 


int ContactBST::exportCSV(Node* ptr,string path)
{
	//ofstream FILE;
	ofstream FILE(path, ios_base::app); //opens file 
	FILE.open(path);	
	int num = 1;
	
		if (ptr == NULL){
			return 0; //if root then return 0
		}

		else{
			ofstream FILE(path, ios_base::app);
			
			num += exportCSV(ptr->left, path); //counts contacts 
			for(int i = 0; i<ptr->contactVector.size(); i++){
				Contact *ct = ptr->contactVector.at(i);
			string fav;
			if(ct->isFav == true){fav = "1";}
			else if(ct->isFav == false){fav = "0";}
			string ans;
			ans = ct->fname+","+ct->lname+","+ct->email+","+ct->primaryPhone+","+ct->city+","+ct->country+","+fav+"\n";
			FILE<<ans;
			}
			
			num += exportCSV(ptr->right, path);

		}
		
	
	FILE.close();
	return num;
} 














