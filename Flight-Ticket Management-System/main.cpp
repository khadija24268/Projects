
//=================================================================================
// Name         : DS Assignment#4 
// Author       : 
// Version      : 1.0
// Date Created : Apr-17-2022
// Date Modified: 
// Description  : Starter Code for Flight-Ticket Management System using HASH TABLE in C++
//=================================================================================
#include<iostream>
#include<cstdlib>
#include<sstream>
#include <chrono>

#include "flightticket.h"
#include "flighthashtable.h"

//==========================================================
void listCommands()
{
	cout<<"\n----------------------------------"<<endl;
	cout<<"import <path>      	:Import flight-tickets from a CSV file"<<endl
		<<"export <path>      	:Export flight-tickets to a CSV file"<<endl
		<<"count_collisions   	:Print number of collisions"<<endl
		<<"add                	:Add a new flight-ticket"<<endl
		<<"delete <key>       	:Delete a flight-ticket"<<endl
		<<"find <key>         	:Find a flight-ticket's details"<<endl
		<<"allinday <date>    	:Display all flight-tickets in a day"<<endl
		<<"printASC <key>     	:Print flight-tickets in ascending order"<<endl
		<<"exit               	:Exit the program"<<endl;
}
//==========================================================

// to be completed with all the necessary method definitions

bool digitcheck(string flightnum){ //checks if user input is a digit or not
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

//==========================================================
int main(void)
{
	FlightHASHTABLE myFlightHASHTABLE;
	FlightHASHTABLE allindaybucket;
	string user_input;
	string command;
	string key;
	string compname, flightnum, coforigin, cofdest, stopover, price, timeofdep , timeofarr, date;
	// int flightno = stoi(flightnum);

	while(true)
	{
		try{
			listCommands();
			cout<<">";
			getline(cin,user_input);
			//to be completed 
			stringstream sstr(user_input);
			getline(sstr,command,' ');
			getline(sstr,key);

			if(command == "add"){
				cout<<"Please enter the details of the Flight: "<<endl<<"Company Name: ";
				cin>>compname;
				cin.ignore(256, '\n');
				cout<<"Flight Number: ";
				cin>>flightnum;
				cin.ignore(256, '\n');
				if(digitcheck(flightnum) == false){cout<<"Invalid Input! Kindly Enter a valid number for Flight Number"<<endl;continue;}
				int flightno = stoi(flightnum);
				cout<<"Country of Origin: ";
				cin>>coforigin;
				cin.ignore(256, '\n');
				cout<<"Country of Destination: ";
				cin>>cofdest;
				cout<<"Stopover: ";
				cin>>stopover;
				cout<<"Price: ";
				cin>>price;
				cout<<"Time of Departure: ";
				cin>>timeofdep;
				cout<<"Time of Arrival: ";
				cin>>timeofarr;
				cout<<"Date: ";
				cin>>date;
				cin.ignore(256, '\n');
				Flight_Ticket* data = new Flight_Ticket(compname, flightno, coforigin, cofdest, stopover, price, timeofdep, timeofarr, date);
				if(myFlightHASHTABLE.add(data)== 1){
					cout<<"SuccessFully Added!"<<endl;
				}else if(myFlightHASHTABLE.add(data)== -1){
					cout<<"Record already exists"<<endl;
				}
				allindaybucket.addallinday(data);
				
			}
			else if(command == "delete" || command == "d"){
				string compname, flightnum;
				int flightno;
				
				stringstream sstr(key);
				getline(sstr,compname,',');
				getline(sstr,flightnum);
				flightno = stoi(flightnum);
				
				myFlightHASHTABLE.removeRecord(compname, flightno);
				cout<<"SuccessFully Deleted!"<<endl;
				
				
				string date = myFlightHASHTABLE.givedate();
				
				
				allindaybucket.removeRecordallinday(compname, flightno, date);
			}
			else if(command == "find"){
				string compname, flightnum;
				int flightno;
				
				stringstream sstr(key);
				getline(sstr,compname,',');
				getline(sstr,flightnum);
				flightno = stoi(flightnum);
				//this code for providing the time is referneced from the internet and modified for the need of the code
				chrono::high_resolution_clock::time_point start = chrono::high_resolution_clock::now();

				myFlightHASHTABLE.find(compname, flightno);

				chrono::high_resolution_clock::time_point end =chrono::high_resolution_clock::now();
				chrono::microseconds elapsed = chrono::duration_cast<chrono::microseconds>(end - start);

				cout << "Time Taken: " << elapsed.count() << " microseconds" << endl;
			
			}
			else if(command == "count" || command == "count_collisions"){
				cout<<"collisions are: "<<myFlightHASHTABLE.count_collisions();
			}
			else if(command == "printASC"){
				string compname, flightnum;
				int flightno;
				
				stringstream sstr(key);
				getline(sstr,compname,',');
				getline(sstr,flightnum);
				flightno = stoi(flightnum);
				myFlightHASHTABLE.printASC(compname, flightno);
			}
			else if(command == "allinday"){
				allindaybucket.allinday(key);
			}
			else if(command == "import" || command == "i"){
				cout<<myFlightHASHTABLE.importCSV(key)<<endl;
				allindaybucket.importCSVallinday(key);
			}
			else if(command == "export"){myFlightHASHTABLE.exportCSV(key);}
			else if(command == "exit"){break;}
			else{cout<<"Invalid Command!"<<endl;}
		}
		catch(exception &ex)
		{
			cout<<ex.what()<<endl;
		}

	}

	return 0;
	return 0;
}
