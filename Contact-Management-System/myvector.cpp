#include <iostream>

#include "myvector.h"


//constructor for vector 
template <typename T> 
MyVector<T>::MyVector(int cap)
{
	this->v_capacity = cap;
	this->data = new T[v_capacity];
	this->v_size = 0;
}

//destructor for vector
template <typename T> 
MyVector<T>::~MyVector()
{
	if(this->data!= NULL){
		delete [] this->data;
	}
}

//function to display the vector elements
template <typename T>
void MyVector<T>::display()
{
	for(int i = 0 ; i<this->v_size ; i++){
		cout<<this->data[i]<<" ";
	}
	cout<<endl;
}

//function to expand the vector capacity when it becomes full / done by changing the capacity of the vector and doubling it 
template <typename T> 
void MyVector<T>:: reserve(int N)
{
	if (this->v_capacity<=N){
		T* arr = new T[N];
		for (int i = 0; i<this->v_size; i++){
			arr[i] = this->data[i];
		}
		if(this->data!= NULL){
			delete [] this->data;
	}
		this->data = arr;
		this->v_capacity = N;
	}
	else {
		return;
	}
}

//function to insert a value at the end of the vector
template <typename T> 
void MyVector<T>:: push_back(T element)
{
	if(this->v_size == this->v_capacity){
		reserve(max(1, 2*v_capacity)); //if the vector is full, the size is doubled to insert the new value 
	}

	this->data[this->v_size] = element;
	this->v_size++;

}

//function to insert a value at some index in the vector 
template <typename T> 
void MyVector<T>:: insert(int index, T element)
{
	if(index > this->v_size-1 || index<0){
		throw out_of_range("out of range!"); 
	}
	if(this->v_size+1>this->v_capacity){
		reserve(max(1, 2*v_capacity)); //if the vector is full, the size is doubled to insert the new value
	}
	for(int i = this->v_size ; i >= index ; i--){
		this->data[i+1] = this->data[i];
	}
	this->data[index] = element;
	this->v_size++;
}

//function to delete an element 
template <typename T> 
void MyVector<T>:: erase(int index)
{
	if (index> this->v_size-1|| index<0){
		throw out_of_range("out of range!"); 
	}
	else{
		for(int i = index ; i<this->v_size ; i++){
			this->data[i] = this->data[i+1];
		}
		this->v_size--;
	}
}

template <typename T>
T& MyVector<T>:: at(int index)
{
	if (index> this->v_size-1|| index<0){
		throw out_of_range("out of range!"); 
	}
	else{
		//T& ans = this->data[index];
		return this->data[index];
	}
}

template <typename T>
const T& MyVector<T>:: front()
{
	if(this->v_size == 0){
		throw out_of_range("Vector empty!");
	}
	else{
		//T& ans = this->data[0];
		return this->data[0];
	}
}

//function to return the last element of the vector 
template <typename T>
const T& MyVector<T>:: back()
{
	if(this->v_size == 0){
		throw out_of_range("Vector empty!");
	}
	else{
		//T& ans = this->data[this->v_size-1];
		return this->data[this->v_size-1];
	}
}

//function to return the size of the vector 
template <typename T>
int MyVector<T>:: size() const
{
	return this->v_size;
}

//function to return the capacity of the vector 
template <typename T>
int MyVector<T>:: capacity() const
{
	return this->v_capacity;
}

//function to return true if vector is empty
template <typename T>
bool MyVector<T>:: empty() const
{
	if(this->v_size == 0){
		return true;
	}
	else{
		return false;
	}
}

//function to change the capcity of the vector so that size equals capacity
template <typename T> 
void MyVector<T>:: shrink_to_fit()
{
	this->v_capacity = this->v_size;
}

template struct MyVector<Contact*>;