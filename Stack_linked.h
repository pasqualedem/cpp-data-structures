#ifndef _STACK_LINKED_
#define _STACK_LINKED_

#include "Stack.h"

template<class T>
class Stack_linked;

template <class T>
class Stack_node{
	friend class Stack_linked<T>;
	private:
		T value;
		Stack_node<T> * next;
};

template <class T>
class Stack_linked : public Stack< T > {
	public:
		typedef typename  Stack<T>::value_type value_type;
		
		Stack_linked();
		Stack_linked(Stack_linked &);
		~Stack_linked();
		void create();
		bool empty() const;
		void pop();
		void push(const value_type & ) ;
		value_type top() const;
		value_type & ref_top() const;
		
		Stack_linked<T>& operator=( Stack_linked<T> && );
		Stack_linked<T>& operator=( const Stack_linked<T>& );
		bool operator==( const Stack_linked<T>& s) const;
	protected:
		Stack_node<T> * head;
		using Stack<T>::length;
		
		static T & getValue(Stack_node<T> * node) {return node->value; }
		static Stack_node<T> * getNext(Stack_node<T> * node) {return node->next; }
};

template <class T>
void Stack_linked<T>::create() {
	length = 0;
}

template< class T >
Stack_linked< T >::Stack_linked(){
	length = 0;
	head = NULL;
}

template< class T >
Stack_linked< T >::Stack_linked(Stack_linked & s){
	Stack_linked<T> app;
	length=0;
	head=NULL;
	while(!s.empty()){
		app.push(s.top());
		s.pop();
	}
	
	while(!app.empty()){
		push(app.top());
		s.push(app.top());
		app.pop();
	}
}
template< class T >
Stack_linked< T >::~Stack_linked(){
	while(!empty())
		pop();
	delete head;
}

template< class T >
bool Stack_linked< T >::empty() const{
	return head==NULL;
}

template< class T >
void Stack_linked< T >::pop(){
	Stack_node<T> * temp;
	temp = head;
	if(!empty()) {
		head = head->next;
		length--;
	}
	delete temp;
}

template< class T >
void Stack_linked< T >::push(const value_type & a){
	Stack_node<T> * temp = new Stack_node<T>;
	temp->value = a;
	temp->next = head;
	head = temp;
	length++;
}

template <class T>
typename Stack_linked<T>::value_type Stack_linked< T >::top() const{
	return head->value;
}

template <class T>
typename Stack_linked<T>::value_type & Stack_linked< T >::ref_top() const{
	return head->value;
}

template<class T>
Stack_linked<T>& Stack_linked<T>::operator=( Stack_linked<T> && s){
	Stack_linked<T> app;
		
	while(!empty())
		pop();
	delete head;
	
	length=0;
	head=NULL;
	while(!s.empty()){
		app.push(s.top());
		s.pop();
	}
	
	while(!app.empty()){
		push(app.top());
		app.pop();
	}
	return *this;
}

template<class T>
Stack_linked<T>& Stack_linked<T>::operator=( const Stack_linked<T> & s){
	if (this != &s){
		length = s.size();
		int i = 0;
		Stack_node<T> * app_node = s.head;
		Stack_linked< T >  app;
		
		while(!empty())
			pop();
		delete head;
		
		length=0;
		head=NULL;
		while(i < s.length){
			app.push(app_node->value);
			app_node = app_node->next;
			i++;
		}
	
		while(!app.empty()){
			push(app.top());
			app.pop();
		}
	}
	return *this;
}

template<class T>
bool Stack_linked<T>::operator==( const Stack_linked<T>& s) const {
	if (length!= s.size())
		return false;
	int i = 0;
	Stack_node<T> * app_node = s.head;
	Stack_node<T> * app_node_2 = head;
	
	while(i < s.length){
		if(app_node->value != app_node_2->value)
			return false;
		
		app_node = app_node->next;
		app_node_2 = app_node_2->next;
		i++;
	}
	return true;
}

#endif
