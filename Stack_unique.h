#ifndef _STACK_UNIQUE_
#define _STACK_UNIQUE_

#include "Stack_linked.h"

template <class T>
class Stack_unique :public Stack_linked<T> {
	public:
		void push (T a);
	private:
		using Stack_linked<T>::length;
		using Stack_linked<T>::head;	
};

template <class T>
void Stack_unique<T>::push(T a) {
	Stack_node<T> * temp;
	temp = head;
	while(temp!=0x0) {
		if(Stack_linked<T>::getValue(temp)== a)
			return;	
		temp = Stack_linked<T>::getNext(temp);	
			}
	Stack_linked<T>::push(a);
}

#endif
