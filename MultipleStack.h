#ifndef _MULTIPLESTACK_
#define _MULTIPLESTACK_
#include "Stack_linked.h"
#include <iostream>

template <class T>
class MultipleStack
{
public:
    MultipleStack (unsigned int);
    void Push (const T&, unsigned int);
    T& Pop (unsigned int);
    
    
    friend std::ostream & operator<< (std::ostream & os, MultipleStack <T> & ms) {
    	os<<"[ ";
		for (int i = 0;i<ms.m-1;i++) {
    		os<<ms.array[i]<<", ";
		}
		os<<ms.array[ms.m-1]<<" ]";
		return os;
	}
    
private:
	Stack_linked<T> * array;
	int m; 
};


template <class T>
MultipleStack<T>::MultipleStack(unsigned int dimension) {
	m = dimension;
	array = new Stack_linked<T> [m];
}

template <class T>
void MultipleStack<T>::Push(const T & value , unsigned int i ) {
	if(i<m) {
		array[i].push(value);
	}	
}

template <class T>
T & MultipleStack<T>::Pop(unsigned int i ) {
	if(i<m) {
		if(!array[i].empty()) {
			T & temp = array[i].ref_top();
			array[i].pop();
			return temp;}
	}	
}

#endif
