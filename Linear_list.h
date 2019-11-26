#ifndef _LISTALIN_H
#define _LISTALIN_H

#include <iostream>

using std::cout;
using std::endl;
using std::ostream;

// classe astratta listaLinare
template< class T, class P >
class Linear_list{
 public:
	typedef T value_type;   // the type of object, T, stored in the list
	typedef P position;
	
	// operators
	virtual void create() = 0;
	virtual bool empty() const = 0; // true if the list's size is 0
	virtual value_type read(position) const = 0;
	virtual void write(const value_type & x, position p) = 0; // write x at position p
	virtual position begin() const = 0;  // returns a position pointing to the beginning of the list
	virtual bool end(position) const = 0; // true with a position pointing to the end of the list
	virtual position next(position) const = 0; // returns the next position
	virtual position previous(position) const = 0; // return the previous position
	virtual void erase(position) = 0;

	// funzioni di servizio
	//friend ostream& operator<< <T,P>(ostream&, const Linear_list<T,P>&);

	/* Altre funzioni di servizio implementabili */
	/*
		virtual int size() const;  // returns the size of the list
		virtual void push_front(const value_type &); // insert a new element at the beginning
		virtual void push_back(const value_type &); // insert a new element at the end
		virtual void pop_front(); // removes the first element
		virtual void pop_back(); // removes the last element
		virtual void clear(); // erases all the elements
	*/
	
	 int size() const  {
		return _length;
			}

	position last() {
		position p = begin();
			int i=1;
		while(i<size()) {
			p = next(p);
			i++; 
			}
		return p;
	}
	
	void inverti(){
		position l = begin();
		position r = last();
		value_type temp;
		int i=0;

		while(i<size()/2) {
			swap(l,r);
			l=next(l);
			r=previous(r);
			i++;
			}
	}
	
	bool isPalindroma(){
		position l = begin();
		position r = last();
		bool palindroma = true;
		value_type temp;

		int i=0;
		while(i<size()/2 && palindroma) {
			palindroma = read(l)==read(r);
			l=next(l);
			r=previous(r);
			i++;
			}
		return palindroma;
	}
	
	void swap(position A, position B){
		value_type temp;
		temp = read(A);
		write(read(B),A);
		write(temp,B);
	}
	
	
	 protected:
		int _length;
};
/* sovraccarica <<. Attenzione se il tipo restituito da read non è primitivo, allora
 * anche per questo tipo bisogna sovraccaricare l'operatore << 
 */
template< class T, class P >
ostream& operator<<(ostream& os, Linear_list<T,P> &l){
	typename Linear_list<T,P>::position p;
	typename Linear_list<T,P>::value_type temp;
	p = l.begin();
	os << "[ ";
	while (!l.end(p)){
		temp = l.read(p);
		if (p != l.begin()) 
			os << ", " << temp ;
		else
			os << temp;
		p = l.next(p);
	}
	os << " ]" ;
	return os;
}

/*
template< class T, class P >
int Linear_list<T,P>::size() const{
   ....
}
*/

#endif // _LISTALIN_H
