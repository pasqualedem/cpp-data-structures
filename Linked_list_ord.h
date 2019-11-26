#ifndef _LINKED_LIST_ORD_H
#define _LINKED_LIST_ORD_H

#include "Linear_list_ord.h"


template<class T>
class Linked_list_ord;

template< class T >
class List_node{
	friend class Linked_list_ord<T>;
 private:
	T _value;
	List_node<T> * _pPrev;
	List_node<T> * _pNext;
};




template< class T >
class Linked_list_ord : public Linear_list_ord<T, List_node<T>*>{
 public:
	typedef typename Linear_list_ord<T, List_node<T>*>::value_type value_type;
	typedef typename Linear_list_ord<T, List_node<T>*>::position position;

	// costruttori
	Linked_list_ord();
	Linked_list_ord(int);
	// costruttore per copia
	Linked_list_ord(const Linked_list_ord<T>& );
	//distruttore
	~Linked_list_ord();

	// operatori
	void create();
	bool empty() const;
	value_type read(position) const;
	void write(const value_type &, position);
	position begin() const;
	position last() const;
	bool end(position) const;
	position next(position) const;
	position previous(position) const;
	void erase(position);
	void insert (const value_type &);
	void fondi(const Linked_list_ord<T> &);
	bool isPalindroma();
	
	
	int size() const {
		return _length;
	}

	// sovraccarico di operatori
	Linked_list_ord<T>& operator=(const Linked_list_ord<T>&); // the assignment operator
	Linked_list_ord<T>& operator=(Linked_list_ord<T>&&);
	bool operator==(const Linked_list_ord<T> &) const; // tests two list for equality

 private:
	List_node<T> * _pHead;
	//int & _length = Linear_list<T,List_node<T>*>::template Linear_list_ord<T, List_node<T>*>::_length; è errato
	using Linear_list_ord<T, List_node<T>*>::_length;
};

template< class T >
Linked_list_ord<T>::Linked_list_ord() {
	_pHead = new List_node<T>;
	_pHead->_pNext = _pHead;
	_pHead->_pPrev = _pHead;
	_length = 0;
}


template< class T >
Linked_list_ord< T >::Linked_list_ord(const Linked_list_ord<T>& L) {
  _length = L.size();

	_pHead = new List_node<T>;
	_pHead->_pNext = _pHead;
	_pHead->_pPrev = _pHead;

	if (!L.empty()){
		position p = L.last();
		for (int i=0; i <= L._length; i++){
			insert(L.read(p), begin());
			p = L.previous(p);
		}
	}
}


template< class T >
Linked_list_ord< T >::~Linked_list_ord(){
	while(!empty())
		erase(begin());
	delete _pHead;
}

template< class T >
void Linked_list_ord< T >::create(){
	if (empty())
			_length = 0;
}

template< class T >
bool Linked_list_ord< T >::empty() const {
	return(_pHead == _pHead->_pNext);
}

template< class T >
typename Linked_list_ord< T >::position
Linked_list_ord< T >::begin() const {
	return (_pHead->_pNext);
}

template< class T >
typename Linked_list_ord< T >::position
Linked_list_ord< T >::last() const {
	return (_pHead->_pPrev);
}


template< class T >
typename Linked_list_ord< T >::position
Linked_list_ord< T >::next(position p) const {
	return(p->_pNext);
}

template< class T >
typename Linked_list_ord< T >::position Linked_list_ord< T >::previous(position p) const {
	if (p != _pHead)
		return(p->_pPrev);
}

template< class T >
bool Linked_list_ord< T >::end(position p) const {
	return(p == _pHead);
}

template< class T >
typename Linked_list_ord< T >::value_type
Linked_list_ord< T >::read(position p) const {
	if (!end(p))
		return(p->_value);
}

template< class T >
void Linked_list_ord< T >::write(const value_type &a, position p) {
	if (!end(p))
    p->_value = a;
}

template< class T >
void Linked_list_ord<T>::insert(const value_type &a){
	position p = begin();
	position t = new List_node<value_type>;
	
	if(!empty())
		while(read(p)<a && (!end(p)))
			p=next(p);
			
	if(p==_pHead)
		_pHead = t;
	t->_value = read(p);
	p->_value = a;
	t->_pNext = p->_pNext;
	t->_pPrev = p;
	p->_pNext->_pPrev = t;
	p->_pNext = t;
	_length++;
}

template< class T >
void Linked_list_ord< T >::erase(position p){
	if (!empty() && !end(p)){
		p->_pPrev->_pNext = p->_pNext;
		p->_pNext->_pPrev = p->_pPrev;
		delete p;
		_length--;
	}
}


template<class T>
Linked_list_ord<T>& Linked_list_ord<T>::operator=(const Linked_list_ord<T>& L){
	if (this != &L){
		
		while(!empty())
			erase(begin());
		delete _pHead;
		
		_length = L.size();

		_pHead = new List_node<T>;
		_pHead->_pNext = _pHead;
		_pHead->_pPrev = _pHead;

		if (!L.empty()){
            position p = L.last();
			for (int i=0; i < L.size(); i++){
				insert(L.read(p));
				p = L.previous(p);
			}
		}
	}
	return *this;
}

template<class T>
Linked_list_ord<T>& Linked_list_ord<T>::operator=(Linked_list_ord<T>&& L){
	if (this != &L){
		
		while(!empty())
			erase(begin());
		delete _pHead;
		
		_length = L.size();

		_pHead = new List_node<T>;
		_pHead->_pNext = _pHead;
		_pHead->_pPrev = _pHead;

		if (!L.empty()){
            position p = L.last();
			for (int i=0; i < L.size(); i++){
				insert(L.read(p));
				p = L.previous(p);
			}
		}
		
		while(!L.empty())
			L.erase(begin());
	}
	return *this;
}

template<class T>
bool Linked_list_ord<T>::operator==(const Linked_list_ord<T> &L) const{
	if (L.size() != _length)
		return false;
	position p, pL;
	p = begin();
	pL = L.begin();
	while (!end(p)){
		if (p->_value != pL->_value)
			return false;
		p = p->_pNext;
		pL = pL->_pNext;
	}
	return true;
}

template <class T>
void Linked_list_ord<T>::fondi (const Linked_list_ord<T> &L) {
	Linked_list_ord<T>::position PL =L.begin();
	while(!L.end(PL)) {
		insert(L.read(PL));
		PL = L.next(PL);
	}
	
}

template <class T>
bool Linked_list_ord<T>::isPalindroma () {
	Linked_list_ord<T>::position PL =next(begin());
	while(!end(PL)) {
		if(read(previous(PL))!=read(PL)) return false;
		PL=next(PL);
	}
	return true;
	
}

#endif // _LINKED_LIST_H
