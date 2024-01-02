#include <iostream>
#include "flightticket.h"

Flight_Ticket::Flight_Ticket(string companyName, int flightNumber, string country_of_origin, string country_of_destination, string stopOver, string price, string time_of_departure, string time_of_arrival, string date){
    this->companyName = companyName;
    this->flightNumber = flightNumber;
    this->country_of_origin = country_of_origin;
    this->country_of_destination = country_of_destination;
    this->stopOver = stopOver;
    this->price = price;
    this->time_of_arrival = time_of_arrival;
    this->time_of_departure = time_of_departure;
    this->date = date;
}

string Flight_Ticket::accessCN(){
    return companyName;
}
string Flight_Ticket::accessFN(){
    string FN = to_string(flightNumber);
    return FN; 
}
string Flight_Ticket::accessCOO(){
    return country_of_origin;
}
string Flight_Ticket::accessCOD(){
    return country_of_destination;
}
string Flight_Ticket::accessstopover(){
    return stopOver;
}
string Flight_Ticket::accessprice(){
    return price;
}
string Flight_Ticket::accessToD(){
    return time_of_departure;
}
string Flight_Ticket::accessToA(){
    return time_of_arrival;
}
string Flight_Ticket::accessdate(){
    return date;
}