#ifndef FlightHASHTABLE_H
#define FlightHASHTABLE_H

#include<iostream>
#include "flightticket.h"
#include "mylist.h"
// include additional header files as needed

using namespace std;

const int SIZE_OF_HASHTABLE = 125003;
// string toLower(string entry);

class HashNode
{
	private:
		string key; // key = companyName+flightNumber
		Flight_Ticket value;
	public:
		HashNode() {};
		HashNode(string key, Flight_Ticket value)
		{
			this->key = key;
			this->value = value;
		}
		string accesskey();
		Flight_Ticket accessvalue();
		friend class FlightHASHTABLE;
};

//=============================================================================
class FlightHASHTABLE
{
	private:
		myList<HashNode> *buckets;				//List of Buckets, Please create your own List Class called MyList
		int size;					    //Current Size of HashTable
		int capacity;
		int collisions;				    // Total Capacity of HashTable
		string removeddate;
		// add more attributes as needed
	public:
		FlightHASHTABLE();						//constructor
		~FlightHASHTABLE();						//destructor
		long hashCode(string key); 						//implement and test different hash functions 
		int importCSV(string path); 			//Load all the flight-tickets from the CSV file to the HashTable
		int exportCSV(string path); 			//Export all the flight-tickets from the HashTable to a CSV file in an ascending order		
		int count_collisions();					//return the number of collisions on the HashTable
		int add(Flight_Ticket* data);			//add new flight to the HashTable
		void removeRecord (string companyName, int flightNumber);	//Delete a record with key from the hashtable
		void find(string companyName, int flightNumber);		//Find and Display records with same key entered 
		void allinday(string date);  					//Find and Display records with same day entered
		void printASC(string companyName, int flightNumber);  		//display the collisions for the entered key in an ascending order 

		// add more methods as needed	
		void printonekey(string key); //to test and print
		int addallinday(Flight_Ticket* data);			//add new flight to the HashTable for allinday
		void removeRecordallinday (string companyName, int flightNumber, string date);	//Delete a record with key from the hashtable for allinday
		string givedate(); //stores the date of the flight removed to give as key in allinday function
		int importCSVallinday(string path); //import for allinday hashtable
		bool digitcheck(string flightnum); //checks user input
};

#endif
