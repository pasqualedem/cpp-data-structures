#ifndef _QUEUE_
#define _QUEUE_

#include <iostream>


template <class T>
class Queue {
	public:
		typedef T value_type;
		
		virtual void create() = 0;
		virtual bool empty() const = 0;
		virtual value_type front() const = 0;
		virtual void enqueue(const value_type &) = 0;
		virtual void dequeue() = 0;
		
		int size() const {
			return length;
		}
		
	protected:
		int length;
};

template< class T >
std::ostream& operator<<(std::ostream& os,  Queue<T> &q){
	os<<"[ ";
	typename Queue<T>::value_type temp;
	for (int i=0;i<q.size();i++){
		temp = q.front();
		os<<temp;
		q.dequeue();
		q.enqueue(temp);
		if(i<q.size()-1)
			os<<" , ";
	}
	os<<" ]";
	return os;
}




#endif
