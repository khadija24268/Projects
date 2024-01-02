#include <iostream>
#include <string>
#include <fstream>
#include <exception>
#include <sstream>
#include <iomanip>
#include <chrono>
#include <thread>

#include "flighthashtable.h"

string HashNode::accesskey() //to access private key
{
    return key;
}
Flight_Ticket HashNode::accessvalue() //to access private value
{
    return value;
}
string FlightHASHTABLE::givedate() //to access date for when passing through allinday functions
{
    
    return removeddate;
}
bool FlightHASHTABLE::digitcheck(string flightnum){ //for user input check 
	if (flightnum.size() == 0){
		return false;
	}
	for(int i = 0 ; i<flightnum.size() ; i++){
		if(!isdigit(flightnum[i])){
			return false;
		}
	}
	return true;
}

FlightHASHTABLE::FlightHASHTABLE() //constructor
{
    this->capacity = SIZE_OF_HASHTABLE;
    this->size = 0;
    this->collisions = 0;
    this->removeddate = "";
    buckets = new myList<HashNode>[capacity];
}
FlightHASHTABLE::~FlightHASHTABLE() //destructor 
{
    delete[] buckets;
}
long FlightHASHTABLE::hashCode(string key) //generates the index for hashtable using the string key
{
    //some of the hash functions are referenced from the internet and then further edited to fit this assignment

    //HashFunction# 1
    unsigned int h = 0;
    for (int i = 0; i < key.length(); i++)
    {
        h = (h << 5) | (h >> 27);
        h += (unsigned int)key[i];
    }
    h %= capacity;
    return h;

    //HashFunction#2
    // unsigned int h = 0;

    // for ( int i = 0 ; i<key.length();i ++){
    //     h += (unsigned int) key[i];
    //     h += (h << 10);
    //     h ^= (h >> 6);
    // }
    // h += (h << 3);
    // h ^= (h >> 11);
    // h += (h << 15);
    //  h = h%capacity;
    // return h;
   

    //HashFunction#3
    // unsigned int h = 0;
    // for (int i=0;i<key.length();i++) {
    //     h = h*29+(unsigned int) key[i];
    // }
    // h %= capacity;
    // return h;

    

	//HashFunction#4
    // unsigned int h = 0;
    // int x = key.length();
    // for(int i = 0; i<key.length();i++){
    //     h = h+ (int(key[i])*(31^(--x)));
    // }
    // h = h%capacity;
    // return h;


    //HashFunction#5
    // unsigned int h = 0;
    // int x = key.length();
    // for(int i = 0 ; i<key.length(); i++){
    //     h = h + x*i + int(key[i]);
    // }
    // h = h%capacity;
    // return h;
	
    //HashFunction#6
    // unsigned int h = 0;
	// for (int i = 0; i < key.length(); i++)
	// {
	// 	h = h + (int(key[i]));
	// }
	// h = h % capacity;
	// return h; 

    
}

int FlightHASHTABLE::add(Flight_Ticket *data) 
{
    string key = data->accessCN() + "," + data->accessFN(); //saves the company name and flight number to pass through hashcode as key
   
    bool same = false;
    int index = hashCode(key); //gets index for adding data
    Node<HashNode> *curr = buckets[index].accesshead(); //temporary node to ietarte over the bucket
    curr = curr->next;
    while (curr != nullptr) 
    {
        if (curr->accesselem().accesskey() == key)
        {
            same = true;//if key is same then collisons are not incremented
            //checks if the exact same data exists already so that it isnt added again
            if (curr->accesselem().accessvalue().accessCOO() == data->accessCOO() && curr->accesselem().accessvalue().accessCOD() == data->accessCOD() && curr->accesselem().accessvalue().accessstopover() == data->accessstopover() && curr->accesselem().accessvalue().accessprice() == data->accessprice() && curr->accesselem().accessvalue().accessToD() == data->accessToD() && curr->accesselem().accessvalue().accessToA() == data->accessToA() && curr->accesselem().accessvalue().accessdate() == data->accessdate())
            {
                return -1;
            }
        }
        curr = curr->next; //changed position of node
    }
    HashNode *newnode = new HashNode(key, *data); //new node with key and data created
    buckets[index].addBack(*newnode); //adds the node at the end of the list
    size = size + 1;
    if (same == false && buckets[index].sizeoflist() > 1)
    {
        collisions = collisions + 1; //if this was a new type of data, increases collisions
    }
   
    return 1;
}

void FlightHASHTABLE::printonekey(string key) //fucntion to test different inputs and display their results
{

    int index = hashCode(key);
    buckets[index].display();
}

void FlightHASHTABLE::removeRecord(string companyName, int flightNumber)
{
    string input;
    int removeindex;
    int count = 0;

    string Flightno = to_string(flightNumber);
    string key = companyName + "," + Flightno; //combines the respective variables to pass them in hashcode function
    int index = hashCode(key);
    Node<HashNode> *curr = buckets[index].accesshead(); //temporary node to iterate over the list
    Node<HashNode> *temp = buckets[index].accesshead();  //temporary node to iterate over list when counting the number of records found 
    if (curr->next == buckets[index].accesstail()) 
    {
        cout << "No record found!" << endl;
        return;
    }
    else
    {
        //to find the number of records found with same key
        for(int i = 0 ; temp != buckets[index].accesstail();  i++){
            if(temp->accesselem().accesskey() == key){
                temp = temp->next;
                count++;
            }
            else{
                temp = temp->next;
            }
        }
        cout<<count<<" records found: "<<endl;
        buckets[index].display();
        //while loop to make sure user inputs the right number when asked to choose
        while (true){
            cout << "Please select the record you want to delete: ";
        cin >> input;
        cin.ignore(256, '\n');
            if (digitcheck(input) == true && stoi(input) <= count){
                break;
            }
            else {
                cout<<"Invalid input!"<<endl;
            }
        }
        removeindex = stoi(input);
        int i;
        //iterates over the list to reach the data user selected to be deleted
        for (i = 0; i < removeindex; i++)
        {
            curr = curr->next;
        }
        string dateremoved = curr->accesselem().accessvalue().accessdate(); //stores the date of the data to pass through delete in allinday functions
        
        this->removeddate = dateremoved;
      
        buckets[index].remove(removeindex); //removes through function of myList
        if (count == 1){
            collisions--;
        }
        
    }
}

void FlightHASHTABLE::find(string companyName, int flightNumber)
{
    string input;
    int count= 0;

    string Flightno = to_string(flightNumber);
    string key = companyName + "," + Flightno;
    int index = hashCode(key); 
    Node<HashNode> *curr = buckets[index].accesshead(); //goes exactly to the bucket where the flight record is stored
    if (curr->next == buckets[index].accesstail()) //if the bucket is empty, it means that no such record exists
    {
        cout << "No record found!" << endl;
        return;
    }
    else
    {
        //iterates to give the exact number of records with the same key 
        for(int i = 0 ; curr != buckets[index].accesstail();  i++){
            if(curr->accesselem().accesskey() == key){
                curr = curr->next;
                count++;
            }
            else{
                curr = curr->next;
            }
        }
        cout << count<<" Records found: " << endl;
        buckets[index].displayforfind();
    }
}

int FlightHASHTABLE::count_collisions()
{

    return collisions; //returns the number of collisions
}

void FlightHASHTABLE::printASC(string companyName, int flightNumber)
{
    string Flightno = to_string(flightNumber);
    string key = companyName + "," + Flightno;
    int index = hashCode(key);
    myList<HashNode> samekeylist; // a temporary list to store the flight details in ascending order of country of destination
    Node<HashNode> *curr = buckets[index].accesshead()->next;
    //iterates over the entire list (bucket) where the record is saved to print all of the flights with same company name and flight number
    for (int i = 0; curr != buckets[index].accesstail(); curr = curr->next)
    {
        if (curr->accesselem().accesskey() == key) //checking if its the same company name and flight number
        {
            if (samekeylist.sizeoflist() == 0) //if temporary list is empty then simply add at the front
            {
                
                samekeylist.addFront(curr->accesselem());
            }
            else if(samekeylist.sizeoflist() != 0) //if not empty
            {
                
                Node<HashNode> *temp = samekeylist.accesshead()->next; //temporary node pointer for iterating over the temporary list
                for (int i = 0; temp != samekeylist.accesstail(); temp = temp->next)
                {
                    if (curr->accesselem().accessvalue().accessCOD() == temp->accesselem().accessvalue().accessCOD()) //if the country of dest is the same then order doesnt matter and can be saved just before the temp node
                    {
                        samekeylist.addBefore(temp, curr->accesselem());
                        
                        break;
                    }
                    else if (temp->next != samekeylist.accesstail()){ //making sure temp is not the last node in the list
                        //if the country of destination if greater than temp but smaller then the one next, then add it in between 
                       if (curr->accesselem().accessvalue().accessCOD() > temp->accesselem().accessvalue().accessCOD() && curr->accesselem().accessvalue().accessCOD() < temp->next->accesselem().accessvalue().accessCOD())
                        {
                            samekeylist.addBefore(temp->next, curr->accesselem());
                            
                            break;
                        }
                    }
                    else if (temp->prev != samekeylist.accesshead()){ //making sure temp is not the first node in this list
                        //if country of dest is less than that of temp but greater than that of node before temp, then add it in between temp and prev
                        if (curr->accesselem().accessvalue().accessCOD() < temp->accesselem().accessvalue().accessCOD() && curr->accesselem().accessvalue().accessCOD() > temp->prev->accesselem().accessvalue().accessCOD())
                        {
                            samekeylist.addBefore(temp, curr->accesselem());
                            
                            break;
                        }
                    }
                    //if the country of dest is greater than the last node then add back
                    else if(curr->accesselem().accessvalue().accessCOD() > temp->accesselem().accessvalue().accessCOD() && temp->next == samekeylist.accesstail()){
                         samekeylist.addBack(curr->accesselem());
                         
                         break;
                    }
                    //if country of dest is smaller than the first node then add front
                    else if(curr->accesselem().accessvalue().accessCOD() < temp->accesselem().accessvalue().accessCOD() && temp->prev == samekeylist.accesshead()){
                         samekeylist.addFront(curr->accesselem());
                         
                         break;
                    }
                }
            }
        }
    }
    samekeylist.display();
}

void FlightHASHTABLE::allinday(string date)
{
    
    int index = hashCode(date);
    myList<HashNode> samekeylist;
    Node<HashNode> *curr = buckets[index].accesshead()->next; //temporary node to iterate over the list
    for (int i = 0; curr != buckets[index].accesstail(); curr = curr->next)
    {
        if (curr->accesselem().accesskey() == date)
        {
            if (samekeylist.sizeoflist() == 0) //if temp list empty then add front
            {
                
                samekeylist.addFront(curr->accesselem());
            }
            else if(samekeylist.sizeoflist() != 0)
            {
                
                Node<HashNode> *temp = samekeylist.accesshead()->next; //temporary list to store records in ascending time of departure
                for (int i = 0; temp != samekeylist.accesstail(); temp = temp->next)
                {
                    if (curr->accesselem().accessvalue().accessToD() == temp->accesselem().accessvalue().accessToD())
                    {
                        samekeylist.addBefore(temp, curr->accesselem());
                        
                        break;
                    }
                    else if (temp->next != samekeylist.accesstail()){//making sure temp is not the last node in the list
                        //if the tim of dep if greater than temp but smaller then the one next, then add it in between 
                       if (curr->accesselem().accessvalue().accessToD() > temp->accesselem().accessvalue().accessToD() && curr->accesselem().accessvalue().accessToD() < temp->next->accesselem().accessvalue().accessToD())
                        {
                            samekeylist.addBefore(temp->next, curr->accesselem());
                            
                            break;
                        }
                    }
                    else if (temp->prev != samekeylist.accesshead()){//making sure temp is not the first node in this list
                        //if time of dep is less than that of temp but greater than that of node before temp, then add it in between temp and prev
                        if (curr->accesselem().accessvalue().accessToD() < temp->accesselem().accessvalue().accessToD() && curr->accesselem().accessvalue().accessToD() > temp->prev->accesselem().accessvalue().accessToD())
                        {
                            samekeylist.addBefore(temp, curr->accesselem());
                            
                            break;
                        }
                    }
                    //if the time of dep is greater than the last node then add back
                    else if(curr->accesselem().accessvalue().accessToD() > temp->accesselem().accessvalue().accessToD() && temp->next == samekeylist.accesstail()){
                         samekeylist.addBack(curr->accesselem());
                         
                         break;
                    }
                    //if time of dep is smaller than the first node then add front
                    else if(curr->accesselem().accessvalue().accessToD() < temp->accesselem().accessvalue().accessToD() && temp->prev == samekeylist.accesshead()){
                         samekeylist.addFront(curr->accesselem());
                         
                         break;
                    }
                }
            }
        }
    }
    samekeylist.display();
}

int FlightHASHTABLE::importCSV(string path)
{

    //===============================================
    string line, compname, flightno, COO, COD, stopover, price, TOD, TOA, date, firstrow;
    

    ifstream fptr(path); // opens the file
    // getline(fptr, line);
    // stringstream s(line); //stores the line in string s
    // getline(s , firstrow, '\n');
    int flightnum;
    long index;
    string key;
    int num = 0;
    if (!fptr.is_open()) //to see if it opens the file or not
    {
        return -1;
    }
    getline(fptr, firstrow, '\n'); //reads the first line of categories
    stringstream s(firstrow);

    while (getline(fptr, line, '\n'))
    {
        // cout<<"here"<<endl;
        stringstream s(line);      // stores the line in string s
        getline(s, compname, ','); // one by one stores the different values in the respective variables
        getline(s, flightno, ',');
        getline(s, COO, ',');
        if (COO[0] == '"')
        {
            string restCOO;
            getline(s, restCOO, ',');
            //restCOO.erase(remove(restCOO.begin(), restCOO.end(), '"'), restCOO.end());
            COO = COO + restCOO;
        }
        getline(s, COD, ',');
        if (COD[0] == '"')
        {
            string restCOD;
            getline(s, restCOD, ',');
            //restCOD.erase(remove(restCOD.begin(), restCOD.end(), '"'), restCOD.end());
            COD = COD + restCOD;
        }

        getline(s, stopover, ',');
        getline(s, price, ',');
        getline(s, TOD, ',');
        if(TOD[1] == ':'){
            TOD = "0"+TOD; //to help compare the times in allinday 
        }
        getline(s, TOA, ',');
        getline(s, date, '\n');

     
        flightnum = stoi(flightno);
        Flight_Ticket *data = new Flight_Ticket(compname, flightnum, COO, COD, stopover, price, TOD, TOA, date); //creates the data structure 
        // string key;
        key = compname + "," + flightno;
        index = hashCode(key); //generates the index for adding data
        HashNode *newnode = new HashNode(key, *data);

        this->add(data); //calls the add function
        // buckets[index].display();

        num++; //counts the number of records imported
        
    }
    fptr.close();
    return num;
}

int FlightHASHTABLE::addallinday(Flight_Ticket *data) //same as add function except the key has changed to date instead
{
    string key = data->accessdate();
    // key = toLower(key);
    bool same = false;
    int index = hashCode(key);
    Node<HashNode> *curr = buckets[index].accesshead();
    curr = curr->next;
    while (curr != nullptr)
    {
        if (curr->accesselem().accesskey() == key)
        {
            same = true;
            if (curr->accesselem().accessvalue().accessCOO() == data->accessCOO() && curr->accesselem().accessvalue().accessCOD() == data->accessCOD() && curr->accesselem().accessvalue().accessstopover() == data->accessstopover() && curr->accesselem().accessvalue().accessprice() == data->accessprice() && curr->accesselem().accessvalue().accessToD() == data->accessToD() && curr->accesselem().accessvalue().accessToA() == data->accessToA() && curr->accesselem().accessvalue().accessdate() == data->accessdate())
            {
                return -1;
            }
        }
        curr = curr->next;
    }
    HashNode *newnode = new HashNode(key, *data);
    buckets[index].addBack(*newnode);
  
    return 1;
}

void FlightHASHTABLE::removeRecordallinday(string companyName, int flightNumber, string date) //same as remove except that key has changed and we are passing date saved from before into this function
{
    string input;
    int removeindex;
    // string key = givedateremoved();
    date.erase(remove(date.begin(), date.end(), '\r'), date.end());
    int index = hashCode(date);
   
    Node<HashNode> *curr = buckets[index].accesshead();
    
    
    if (curr->next == buckets[index].accesstail())
    {
        return;
    }
    else
    {
        curr = curr->next;
        for (int i = 0; curr != buckets[index].accesstail(); i++)
        {
            if (curr->accesselem().accessvalue().accessCN() == companyName && stoi(curr->accesselem().accessvalue().accessFN()) == flightNumber)
            {
                
                curr->next->prev = curr->prev;
                curr->prev->next = curr->next;
                delete curr;
                
            }
            curr = curr->next;
        }
    }
}

int FlightHASHTABLE::importCSVallinday(string path) //same as import with just the key changed to date when creating new node
{

    //===============================================
     string line, compname, flightno, COO, COD, stopover, price, TOD, TOA, date, firstrow;
    // string restCOO, restCOD;

    ifstream fptr(path); // opens the file
   
    int flightnum;
    long index;
    string key;
    int num = 0;
    if (!fptr.is_open())
    {
        return -1;
    }
    getline(fptr, firstrow, '\n');
    stringstream s(firstrow);

    while (getline(fptr, line, '\n'))
    {
        // cout<<"here"<<endl;
        stringstream s(line);      // stores the line in string s
        getline(s, compname, ','); // one by one stores the different values in the respective variables
        getline(s, flightno, ',');
        getline(s, COO, ',');
        if (COO[0] == '"')
        {
            string restCOO;
            getline(s, restCOO, ',');
            //restCOO.erase(remove(restCOO.begin(), restCOO.end(), '"'), restCOO.end());
            COO = COO + restCOO;
        }
        getline(s, COD, ',');
        if (COD[0] == '"')
        {
            string restCOD;
            getline(s, restCOD, ',');
            //restCOD.erase(remove(restCOD.begin(), restCOD.end(), '"'), restCOD.end());
            COD = COD + restCOD;
        }

        getline(s, stopover, ',');
        getline(s, price, ',');
        getline(s, TOD, ',');
        if(TOD[1] == ':'){
            TOD = "0"+TOD;
        }
        getline(s, TOA, ',');
        getline(s, date, '\r');
        date.erase(remove(date.begin(), date.end(), '\n'), date.end());
   
        flightnum = stoi(flightno);
        Flight_Ticket *data = new Flight_Ticket(compname, flightnum, COO, COD, stopover, price, TOD, TOA, date);
       
        index = hashCode(date);

        HashNode *newnode = new HashNode(key, *data);

        this->addallinday(data);
       

        num++;
      
    }
    fptr.close();
    return num;
}

int FlightHASHTABLE::exportCSV(string path){
    ofstream FILE(path); //opens file 
	
	int num = 1;

	
		if (!FILE){ //outputs error
            cout<<"Not Working"<<endl;
			return -1; 
		}

		else{
			
            HashNode input; //to store the data into this node 
            //iterating over the entire hashtable
            for(int i = 0; i < this->capacity ; i++){
                Node<HashNode>* curr = buckets[i].accesshead()->next;
                //iterating over the bucket (list)
                while(curr != buckets[i].accesstail()){
                    input = curr->accesselem(); //stores element
                    
                    //inserts all the values
                    FILE<<input.accessvalue().accessCN()<<","<<input.accessvalue().accessFN()<<","<<input.accessvalue().accessCOO()<<","<<input.accessvalue().accessCOD()<<","<<input.accessvalue().accessstopover()<<","<<input.accessvalue().accessprice()<<","<<input.accessvalue().accessToD()<<","<<input.accessvalue().accessToA()<<","<<input.accessvalue().accessdate()<<endl;
                    num++; //to track record numbers
                    curr = curr->next;
                }
            }
           
		}
		
	
	FILE.close(); //closes file
	return num;
}