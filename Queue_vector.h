#ifndef _QUEUE_VECTOR_
#define _QUEUE_VECTOR_

#include "Queue.h"


template <class T>
class Queue_vector : public Queue<T> {
	public:
		typedef typename Queue<T>::value_type value_type;
		
		Queue_vector<T>();
		Queue_vector(Queue_vector &);
		~Queue_vector();
		void create();
		bool empty() const;
		value_type front() const;
		value_type & ref_front() const;
		void enqueue(const value_type &);
		void dequeue() ;
		
		Queue_vector<T>& operator=( const Queue_vector<T>& );
		Queue_vector<T>& operator=( Queue_vector<T>&& );
		bool operator==( const Queue_vector<T>& q) const;
		
	private:
		void array_doubling();
		
		value_type * SPACE;
		int head;
		int tail;
		using Queue<T>::length;
		int space_size;
};

template <class T>
Queue_vector<T>::Queue_vector() {
	space_size = 4;
	head = 0;
	tail = 0;
	length = 0;
	SPACE = new value_type[space_size];
}

template <class T>
Queue_vector<T>::Queue_vector(Queue_vector & q ) {
	SPACE = new value_type[q.space_size];
	space_size = q.space_size;
	value_type temp;
	head = 0;
	tail = 0;
	length = 0;
	for(int i=0;i<q.size();i++){
		temp = q.front();
		q.dequeue();
		q.enqueue(temp);
		enqueue(temp);
	}
}

template <class T>
Queue_vector<T>::~Queue_vector() {
	delete[] SPACE;
}

template <class T>
void Queue_vector<T>::create () {
	length = 0;
}

template <class T>
bool Queue_vector<T>::empty() const {
	return head == tail;
}

template <class T>
typename Queue_vector<T>::value_type Queue_vector<T>::front() const{
	return SPACE[head];
}

template <class T>
typename Queue_vector<T>::value_type & Queue_vector<T>::ref_front() const{
	return SPACE[head];
}

template <class T>
void Queue_vector<T>::enqueue(const value_type & element) {
	if((tail+1)%space_size == head)
		array_doubling();
		
	SPACE[tail] = element;

	tail = (tail+1)%space_size;
	
	length++;
}

template <class T>
void Queue_vector<T>::dequeue() {
	if(!empty()) {
		head=(head+1)%space_size;
		length--;
	}
}

template <class T>
void Queue_vector<T>::array_doubling() {
	value_type * SPACE_app = new value_type[space_size*2];;
	int i = 0;
	int length_app = Queue<T>::size();
	while(!(empty())){
		SPACE_app[i] = front();
		dequeue();
		i++;
	}
	head = 0;
	tail = length_app;
	length = length_app;
	space_size = space_size*2;
	delete[] SPACE;
	SPACE = SPACE_app;
}

template<class T>
Queue_vector<T>& Queue_vector<T>::operator=( const Queue_vector<T>& q){
	if (this != &q){
		delete[] SPACE;
		SPACE = new value_type[q.space_size];
		space_size = q.space_size;
		value_type temp;
		head = 0;
		tail = 0;
		length = 0;
		for(int i=0;i<q.size();i++){
			temp = q.SPACE[(head+i)%q.space_size];
			enqueue(temp);
		}
	}
	return *this;
}

template <class T>
Queue_vector<T>& Queue_vector<T>::operator=( Queue_vector<T>&& q) {
	delete[] SPACE;
	SPACE = new value_type[q.space_size];
	space_size = q.space_size;
	value_type temp;
	head = 0;
	tail = 0;
	length = 0;
	for(int i=0;i<q.size();i++){
		temp = q.front();
		q.dequeue();
		enqueue(temp);
	}
}

template<class T>
bool Queue_vector<T>::operator==( const Queue_vector<T>& q) const{
	if (length != q.size())
		return false;
		

	for(int i=0;i<q.size();i++){
		if( q.SPACE[(head+i)%q.space_size] != SPACE[(head+i)%q.space_size])
			return false;
	}
	
	return true;
}



#endif
