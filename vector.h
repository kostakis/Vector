#pragma once
#ifndef VECTOR_H
#define VECTOR_H

#include <iostream>
#include <initializer_list>

using std::cout;
using std::cerr;
using std::endl;

template<class T> class Vector {
private:
	/*An array holding all the data*/
	T* __elem;
	/*Size of the vector*/
	size_t __size;
	/*Current allocated size of the vector*/
	size_t __capacity;
public:
	/*Empty constructor*/
	Vector() :__elem(NULL), __size(0), __capacity(0) {}

	/*Constructor given the size*/
	Vector(size_t cap) {
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
		for (size_t i = 0; i < vec.size(); i++) {
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
	size_t size() const;
	bool isEmpty() const;
	T& at(size_t pos) const;


	void push_back(const T & elem);
	void deletePos(size_t pos);
	void clear();

	/*Operators*/
	T& operator [](size_t pos) const;

};

template<class T>
inline size_t Vector<T>::size() const
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
inline T & Vector<T>::at(size_t pos) const
{
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
		for (size_t i = 0; i < __size; i++) {
			copy[i] = __elem[i];
		}
		__elem = new T[__capacity * 2];
		__capacity = __capacity * 2;
		for (size_t i = 0; i < __size; i++) {
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
void Vector<T>::deletePos(size_t pos)
{
	for (size_t i = pos; i < __size; i++) {
		__elem[i] = __elem[i + 1];
	}
	__size--;
}



template<class T>
void Vector<T>::clear()
{
	for (size_t  i = 0; i < __size; i++) {
		__elem[i] = NULL;
	}
	__size = 0;
}


/*
Return value of then index given
*/
template<class T>
inline T & Vector<T>::operator[](size_t pos) const
{
	return __elem[pos];
}

#endif