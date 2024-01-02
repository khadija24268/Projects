#include <iostream>
#include "flighthashtable.h"
#include "mylist.h"

template <typename E> Node<E>* myList<E>::accesshead(){
	return head;
}
template <typename E> Node<E>* myList<E>::accesstail(){
	return tail;
}

template <typename E> myList<E>::myList ()
{
	//todo
	
	head = new Node<E>;
	tail = new Node<E>;
	head->next = tail;
	tail->prev = head;
	
}
//============================================================
template <typename E> myList<E>::~myList () // destructor to clean up all nodes
{
	//todo
	if (!empty()){
		removeFront(); 
	}
	delete head;
	delete tail;
}
//============================================================
template <typename E> bool myList<E>::empty() const // is list empty?
{
	//todo
	if(head->next == tail && tail -> prev == head){
		return true;
	}
	else {return false;}
}
//============================================================
template <typename E> const E& myList<E>::front(E& error) const // get front element
{
	//todo
	if (!empty()){
		Node<E>* curr = head->next;
		return curr->elem;
	}
	else{
		throw runtime_error("List is empty!");
	}
}
//============================================================
template <typename E> const E& myList<E>::back(E& error) const // get back element
{
	//todo
	if (!empty()){
		Node<E>* curr = tail->prev;
		return curr->elem;
	}
	else{
		throw runtime_error("List is empty!");
	}
}
//============================================================
template <typename E> void myList<E>::addBefore(Node<E> *ptr, const E& elem) //adds an element before a specific node
{
	//todo
	if (!empty()){
		Node<E>* newnode = new Node<E>(elem);
		newnode->next = ptr;
		newnode->prev = ptr->prev;
		ptr->prev->next = newnode;
		ptr->prev = newnode;
	}
	else{
		cout<<"List is empty"<<endl;
	}
	

}
//============================================================
template <typename E> void myList<E>::addFront(const E& elem) // add to front of list
{
	//todo
	Node<E>* newnode = new Node<E> (elem);
	Node<E> * curr = head->next;
	newnode -> next = curr;
	newnode ->prev = head;
	head -> next = newnode;
	curr -> prev = newnode;	
	
}
//============================================================
template <typename E> void myList<E>::addBack(const E& elem) // add to Back of the list
{
	//todo
	Node<E>* newnode = new Node<E>(elem);
	Node<E>* curr = tail->prev;
	newnode -> next = tail;
	newnode -> prev = curr;
	tail->prev = newnode;
	curr->next = newnode;

}
//============================================================
template <typename E> void myList<E>::removeFront() // remove front item from list
{
	//todo
	if (!empty()){
		Node<E>* curr = head->next;
		head->next = curr->next;
		curr->next->prev = head;
		delete curr;
	}
	else{cout<<"List is empty"<<endl;}
	

}
//============================================================
template <typename E> void myList<E>::removeBack() // remove last item from list
{
	//todo
	if(!empty()){
		Node<E>* curr = tail -> prev;
		tail -> prev = curr -> prev;
		curr -> prev -> next = tail;
		delete curr;
	}
	else{cout<<"List is empty"<<endl;}
	
}
//============================================================
template <typename E> void myList<E>::display() const
{
	Node<E>* curr = head->next;
	for(int i = 0 ; curr!= tail ; i++){ //iterates over the entire list
		cout<<i+1<<"."<<curr->accesselem().accessvalue().accessCN()<<" , ";
		cout<<curr->accesselem().accessvalue().accessFN()<<" , ";
		cout<<curr->accesselem().accessvalue().accessCOO()<<" , ";
		cout<<curr->accesselem().accessvalue().accessCOD()<<" , ";
		cout<<curr->accesselem().accessvalue().accessstopover()<<" , ";
		cout<<curr->accesselem().accessvalue().accessprice()<<" , ";
		cout<<curr->accesselem().accessvalue().accessToD()<<" , ";
		cout<<curr->accesselem().accessvalue().accessToA()<<" , ";
		cout<<curr->accesselem().accessvalue().accessdate()<<endl;
		curr = curr->next;
	}
}

//============================================================
template <typename E> int myList<E>::sizeoflist() const
{
	int counter=0;
	Node<E>* curr = head;
	while(curr->next!= tail){ //iterates over the list untill the last node reached
		curr = curr->next;
		counter = counter +1;
	}
	return counter;
}
//============================================================

template <typename E> void myList<E>::remove(int index)
{
	Node<E>* curr = head;
	for(int i = 0 ; i<sizeoflist() ; i++){ //iterates utill the required node at index is reached
		if(i == index){
			break;
		}else{
			curr = curr->next;
		}
	}
	curr->next->prev = curr->prev;
	curr->prev->next = curr->next;
	delete curr;
}

template <typename E> void myList<E>::displayforfind() const //displays the records in a specific way for find function in hashtable 
{
	Node<E>* curr = head;
	for(int i = 0 ; curr->next!= tail ; i++){
		curr = curr->next;
		cout<<i+1<<"."<<endl;
		cout<<"Company name: "<<curr->accesselem().accessvalue().accessCN()<<endl;
		cout<<"Flight number: "<<curr->accesselem().accessvalue().accessFN()<<endl;
		cout<<"Country of Origin: "<<curr->accesselem().accessvalue().accessCOO()<<endl;
		cout<<"Country of Destination: "<<curr->accesselem().accessvalue().accessCOD()<<endl;
		cout<<"StopOver: "<<curr->accesselem().accessvalue().accessstopover()<<endl;
		cout<<"Price: "<<curr->accesselem().accessvalue().accessprice()<<endl;
		cout<<"Time of Departure: "<<curr->accesselem().accessvalue().accessToD()<<endl;
		cout<<"Time of Arrival: "<<curr->accesselem().accessvalue().accessToA()<<endl;
		cout<<"Date: "<<curr->accesselem().accessvalue().accessdate()<<endl;
	}
}


template <typename E> void myList<E>::givedate(int index)
{
	Node<E>* curr = head;
	cout<<"index"<<index<<"SOL:  "<<sizeoflist()<<endl;
	for(int i = 0 ; i<sizeoflist() ; i++){
		cout<<"i"<<i<<"index"<<index<<endl;
		if(i == index){
			cout<<"I come here"<<endl;
			break;
		}else{
			curr = curr->next;
		}
	}
	cout<<curr->accesselem().accessvalue().accessdate()<<"Here"<<endl;
}
//template struct myList<HashNode>;
template class myList<HashNode>;







