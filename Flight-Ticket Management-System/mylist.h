
#include<iostream>
#include<string>
#include<sstream>
#include<iomanip>
#include<exception>
#pragma once
using namespace std;

template <typename E> class myList ;
template <typename E> class Node
{
	private:
		E elem; //data element (type string in this case)
		Node<E>* next; //Link (pointer) to the next Node
		Node<E>* prev; //Link (pointer) to the previous Node
	
		friend class myList<E>;
		friend class FlightHASHTABLE;
		
	public:
		Node(): next(NULL), prev(NULL)
		{}
		Node(E elem) : elem(elem), next(NULL), prev(NULL)
		{}
		E& accesselem(){
			return elem;
		}

}; 
//==============================================================
template <typename E> class myList 
{
	private:
		Node<E>* head; 	// pointer to the head of List
		Node<E>* tail;// pointer to the tail of List
		
	public:
		myList (); // constructor to create dummy head and tail nodes
		~myList (); // destructor to clean up all nodes
		bool empty() const; // return true if the list is empty
		const E& front(E& error) const; // return the element from the first valid Node of list, throw an exception if the list is empty
		const E& back(E& error) const;  // get the value (element) from last valid Node of the list, throw an exception if the list is empty
		void addBefore(Node<E> *ptr, const E& elem);	 //add a new node before a node pointed by ptr
		void addFront(const E& elem); // add a new node to the front of list (after head)
		void addBack(const E & elem); //add a new node to the back of the list (before tail)
		void removeFront(); // remove front node from list, throw an exception if the list is empty
		void removeBack();  // remove last node from list, throw an exception if the list is empty
		void display() const;	// display all element of the list
		int sizeoflist() const;
		void remove(int index);
		void displayforfind() const;

		Node<E>* accesshead();
		Node<E>* accesstail();
		void givedate(int index);
		

		friend class FlightHASHTABLE;
};

