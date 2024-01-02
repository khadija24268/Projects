#include<iostream>
#include "contact.h"

//constructor for the class Contact
Contact::Contact(string fname, string lname, string email, string primaryPhone, string city, string country, bool isFav){
	this->fname = fname;
	this->lname = lname;
	this->email = email;
	this->primaryPhone = primaryPhone;
	this->city = city;
	this->country = country;
	this->isFav = isFav;
}

// int main(){

// }