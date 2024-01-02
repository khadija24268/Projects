#ifndef FLIGHT_TICKET_H
#define FLIGHT_TICKET_H

#include<iostream>
using namespace std;

class Flight_Ticket
{
	private:
		string companyName;
		int flightNumber;
		string country_of_origin;
		string country_of_destination;
		string stopOver;
		string price;
		string time_of_departure;
		string time_of_arrival;
		string date;

	public:
		Flight_Ticket(){};
		Flight_Ticket(string companyName, int flightNumber, string country_of_origin, string country_of_destination, string stopOver, string price, string time_of_departure, string time_of_arrival, string date);
		// add additional methods as needed
		string accessCN();
		string accessFN();
		string accessCOO();
		string accessCOD();
		string accessstopover();
		string accessprice();
		string accessToD();
		string accessToA();
		string accessdate();
};

#endif
