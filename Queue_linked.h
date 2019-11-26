#ifndef _QUEUE_LINKED_
#define _QUEUE_LINKED_

#include "Queue.h"

template <class T>
class Queue_linked;

template <class T>
class Queue_node {
	friend class Queue_linked<T>;
	private:
		T value;
		Queue_node<T> * next;		
};


template <class T>
class Queue_linked : public Queue<T> {
	public:
		typedef typename Queue<T>::value_type value_type;
		
		Queue_linked<T>();
		Queue_linked(Queue_linked &);
		~Queue_linked();
		void create();
		bool empty() const;
		value_type front() const;
		value_type & ref_front() const; // returns the reference of the front
		void enqueue(const value_type &);
		void dequeue() ;
		
		Queue_linked<T>& operator=( const Queue_linked<T>&);
		Queue_linked<T>& operator=( Queue_linked<T>&&);
		bool operator==( const Queue_linked<T>& q) const;
		
	private:
		Queue_node<T> * head;
		Queue_node<T> * tail;
		using Queue<T>::length;
};

template <class T>
Queue_linked<T>::Queue_linked() {
	head = 0x0;
	tail = 0x0;
	length = 0;
}

template <class T>
Queue_linked<T>::Queue_linked(Queue_linked & q ) {
	value_type temp;
	head = 0x0;
	tail = 0x0;
	length = 0;
	for(int i=0;i<q.size();i++){
		temp = q.front();
		q.dequeue();
		q.enqueue(temp);
		enqueue(temp);
	}
}

template <class T>
Queue_linked<T>::~Queue_linked() {
	while(!empty())
		dequeue();
	delete head;
	delete tail;
}

template <class T>
void Queue_linked<T>::create () {
	length = 0;
}

template <class T>
bool Queue_linked<T>::empty() const {
	return head == 0x0;
}

template <class T>
typename Queue_linked<T>::value_type Queue_linked<T>::front() const{
	return head->value;
}

template <class T>
typename Queue_linked<T>::value_type & Queue_linked<T>::ref_front() const{
	return head->value;
}

template <class T>
void Queue_linked<T>::enqueue(const value_type & element) {
	Queue_node<T> * node = new Queue_node<T>;
	if(!empty())
		tail->next = node;
	node->next = 0x0;
	node->value = element;
	tail = node;
	if(empty())
		head = node;
	length++;
}

template <class T>
void Queue_linked<T>::dequeue() {
	Queue_node<T> * node = head;
	if(!empty()) {
		head = head->next;
		delete node;
		length--;
	}
	if(length==0)
		tail=0x0;
}

template<class T>
Queue_linked<T>& Queue_linked<T>::operator=( const Queue_linked<T>& q){
	if (this != &q){
		Queue_node<T> * temp_node = q.head;
		
		while(!empty())
			dequeue();
		delete head;
		
		head = 0x0;
		tail = 0x0;
		length = 0;
		
		for(int i=0;i<q.size();i++){
			enqueue(temp_node->value);
			temp_node = temp_node->next;
		}
	}
	return *this;
}

template<class T>
Queue_linked<T>& Queue_linked<T>::operator=( Queue_linked<T>&& q){
	value_type temp;
	
	while(!empty())
		dequeue();
	delete head;
	head = 0x0;
	tail = 0x0;
	length = 0;
	int q_length = q.size();
	for(int i=0;i<q_length;i++){
		temp = q.front();
		q.dequeue();
		enqueue(temp);
	}
	return *this;
}

template<class T>
bool Queue_linked<T>::operator==( const Queue_linked<T>& q) const {
	if (length!=q.size()) 
		return false;
	Queue_node<T> * temp_node = q.head;
	Queue_node<T> * temp_node_2 = head;

		for(int i=0;i<q.size();i++){
			if(temp_node->value != temp_node_2->value)
				return false;
			temp_node = temp_node->next;
			temp_node_2 = temp_node_2->next;
		}
	return true;
}




#endif
