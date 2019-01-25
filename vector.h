#pragma once
#ifndef VECTOR_H
#define VECTOR_H

#include<iostream>
#include <initializer_list>
#include <exception>

using std::cout;
using std::cerr;
using std::endl;

template<class T> class Vector {
private:
	/*An array holding all the data*/
	T* __elem;
	/*Size of the vector*/
	unsigned __size;
	/*Current allocated size of the vector*/
	unsigned __capacity;
public:
	/*Empty constructor*/
	Vector() :__elem(NULL), __size(0), __capacity(0) {}

	/*Constructor given the size*/
	Vector(unsigned cap) {
		if (cap < 0) {
			throw std::invalid_argument("Invalid argument");
		}
		__elem = new T[cap];
		__size = 0;
		__capacity = cap;
	}
	~Vector() {
		delete[] __elem;
	}

	/*Copy constructor*/
	Vector(const Vector & vec) {
		__elem = new T[vec.size()];
		__size = 0;
		__capacity = vec.size();
		for (unsigned i = 0; i < vec.size(); i++) {
			__elem[i] = vec[i];
			__size++;
		}
	}

	/*Initializer list constructor*/
	Vector(std::initializer_list<T> list) {
		__size = 0;
		__capacity = list.size();
		__elem = new T[list.size()];
		for (auto x : list) {
			__elem[__size] = x;
			__size++;
		}
	}


	/*Accessors*/
	unsigned size() const;
	bool isEmpty() const;
	T& at(unsigned pos) const;//And Modifier


	void push_back(const T & elem);
	void deletePos(unsigned pos);
	void clear();

	/*Operators*/
	T& operator [](unsigned pos) const;

};

template<class T>
inline unsigned Vector<T>::size() const
{
	return __size;
}

template<class T>
inline bool Vector<T>::isEmpty() const
{
	if (__size == 0) {
		return true;
	}
	else {
		return false;
	}
}

template<class T>
inline T & Vector<T>::at(unsigned pos) const
{
	if (pos >= __size || pos<0 ) {
		throw std::out_of_range("Out of range exception");
	}

	return __elem[pos];
}


/*
Insert an element and the end of the vector
If capacity is not  enough we allocate x2 the previous capicity
*/
template<class T>
void Vector<T>::push_back(const T & elem)
{
	if (__size == 0 && __capacity == 0) {
		__elem = new T[1];
		__elem[__size] = elem;
		__size++;
		__capacity++;
		return;
	}

	if (__size == __capacity) {
		T* copy = new T[__capacity];
		for (int i = 0; i < __size; i++) {
			copy[i] = __elem[i];
		}
		__elem = new T[__capacity * 2];
		__capacity = __capacity * 2;
		for (unsigned i = 0; i < __size; i++) {
			__elem[i] = copy[i];
		}
		__elem[__size] = elem;
		__size++;
		delete[] copy;
		return;
	}

	__elem[__size] = elem;
	__size++;
}

/*
Deletes an element from the vector and rezises it
No Bounds checking
*/
template<class T>
void Vector<T>::deletePos(unsigned pos)
{
	/*
	if (pos<0 || pos>=__size) {
		std::cerr << "Wrong position exiting" << std::endl;
		exit(-1);
	}
	*/

	for (unsigned i = pos; i < __size; i++) {
		__elem[i] = __elem[i + 1];
	}
	__size--;
}



template<class T>
inline void Vector<T>::clear()
{
	for (unsigned int i = 0; i < __size; i++) {
		__elem[i] = NULL;
	}
	__size = 0;
}


/*
Return value of then index given
No Bounds checking
*/
template<class T>
inline T & Vector<T>::operator[](unsigned pos) const
{
	/*
	if (pos<0 || pos>=__capacity) {
		cerr << "Wrong position exiting" << endl;
		exit(-1);
	}
	*/
	return __elem[pos];
}

#endif