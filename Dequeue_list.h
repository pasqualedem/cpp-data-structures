#ifndef _DEQUEUE_LIST_
#define _DEQUEUE_LIST_

#include "Linked_list.h"
#include <iostream>

template <class T>
class Dequeue_list {
	public:
		Dequeue_list();
		Dequeue_list(const Dequeue_list &);
		
		bool empty();
		int size();
		void enqueue_right(const T &);
		void enqueue_left (const T &);
		void dequeue_right();
		void dequeue_left();
		T left();
		T right();
		
		friend std::ostream & operator<<(std::ostream & os, Dequeue_list dl) {
			os<<dl.elements;
			return os;
		}
	private:
		Linked_list<T> elements;
};

template<class T>
Dequeue_list<T>::Dequeue_list() {
}

template<class T>
Dequeue_list<T>::Dequeue_list(const Dequeue_list<T> & dl) {
	elements = dl.elements;
}

template<class T>
bool Dequeue_list<T>::empty() {
	return elements.empty();
}

template<class T>
int Dequeue_list<T>::size() {
	return elements.size();
}

template<class T>
void Dequeue_list<T>::enqueue_right(const T & value) {
	elements.insert(value);
}

template<class T>
void Dequeue_list<T>::enqueue_left(const T & value) {
	elements.insert(value,elements.begin());
}

template<class T>
void Dequeue_list<T>::dequeue_right() {
	elements.erase(elements.last());
}

template<class T>
void Dequeue_list<T>::dequeue_left() {
	elements.erase(elements.begin());
}

template<class T>
T Dequeue_list<T>::left() {
	return elements.read(elements.last());
}

template<class T>
T Dequeue_list<T>::right() {
	return elements.read(elements.begin());
}

#endif
