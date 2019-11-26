#ifndef _STACK_
#define _STACK_

#include <iostream>

template <class T>
class Stack {
	public:
		typedef T value_type ;
		
		virtual void create() = 0;
		virtual bool empty() const = 0;
		virtual void pop() = 0;
		virtual void push(const value_type &) = 0;
		virtual value_type top() const = 0;
		
		
		
		int size() const {
			return length;
		}
		
	void print(std::ostream& os,  Stack<T> &s) {
		typename Stack<T>::value_type temp;
		if (!s.empty()){
			temp = s.top();
			os<<temp;
			s.pop();
			if(!s.empty())
				os<<" , ";
			s.print(os,s);
			s.push(temp);
			}
	}
		
	protected:
		int length;
};

template< class T >
std::ostream& operator<<(std::ostream& os,  Stack<T> &s){
	os<<"[ ";
	s.print(os,s);
	os<<" ]";
}


#endif
