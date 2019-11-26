#ifndef _LINKED_LIST_H
#define _LINKED_LIST_H

#include "linear_list.h"

template<class T>
class Linked_list;

template< class T >
class List_node_ord{
	friend class Linked_list<T>;
 private:
	T _value;
	List_node_ord<T> * _pPrev;
	List_node_ord<T> * _pNext;
};




template< class T >
class Linked_list : public Linear_list<T, List_node_ord<T>*>{
 public:
	typedef typename Linear_list<T, List_node_ord<T>*>::value_type value_type;
	typedef typename Linear_list<T, List_node_ord<T>*>::position position;

	// costruttori
	Linked_list();
	Linked_list(int);
	// costruttore per copia
	Linked_list(const Linked_list<T>& );
	//distruttore
	~Linked_list();

	// operatori
	void create();
	bool empty() const;
	value_type & ref_read(position p);
	value_type read(position) const;
	void write(const value_type &, position);
	position begin() const;
	position last() const;
	bool end(position) const;
	position next(position) const;
	position previous(position) const;
	void insert(const value_type & a , position p);
	void push_back(const value_type & a);
	void push_front(const value_type & a);
	void erase(position);

	// sovraccarico di operatori
	Linked_list<T>& operator=(const Linked_list<T>&); // the assignment operator
	Linked_list<T>& operator=( Linked_list<T>&&); 
	bool operator==(const Linked_list<T> &) const; // tests two list for equality

 private:
	List_node_ord<T> * _pHead;
	using Linear_list<T, List_node_ord<T>*>::_length; // the length of the list
};

template< class T >
Linked_list< T >::Linked_list() {

	_pHead = new List_node_ord<T>;
	_pHead->_pNext = _pHead;
	_pHead->_pPrev = _pHead;
	_length = 0;
 }

template< class T >
Linked_list< T >::Linked_list(const Linked_list<T>& L) {
    _length = 0;
	_pHead = new List_node_ord<T>;
	_pHead->_pNext = _pHead;
	_pHead->_pPrev = _pHead;
	if (!L.empty()){
		position p = L.last();
		for (int i=0; i < L.size(); i++){
			insert(L.read(p), begin());
			p = L.previous(p);
		}
	}
}
	


template< class T >
Linked_list< T >::~Linked_list(){
	while(!empty())
		erase(begin());
	delete _pHead;
}

template< class T >
void Linked_list< T >::create(){
	if (empty())
			_length = 0;
}

template< class T >
bool Linked_list< T >::empty() const {
	if(_pHead != 0x0)
		return(_pHead == _pHead->_pNext);
	return true;
}

template< class T >
typename Linked_list< T >::position
Linked_list< T >::begin() const {
	return (_pHead->_pNext);
}

template< class T >
typename Linked_list< T >::position
Linked_list< T >::last() const {
	return (_pHead->_pPrev);
}


template< class T >
typename Linked_list< T >::position
Linked_list< T >::next(position p) const {
	return(p->_pNext);
}

template< class T >
typename Linked_list< T >::position Linked_list< T >::previous(position p) const {
	if (p != _pHead)
		return(p->_pPrev);
}

template< class T >
bool Linked_list< T >::end(position p) const {
	return(p == _pHead);
}

template< class T >
typename Linked_list< T >::value_type
Linked_list< T >::read(position p) const {
	if (!end(p))
		return(p->_value);
}

template< class T >
typename Linked_list< T >::value_type &
Linked_list< T >::ref_read(position p)  {
	if (!end(p))
		return (p->_value);
}

template< class T >
void Linked_list< T >::write(const value_type &a, position p) {
	if (!end(p))
    p->_value = a;
}

template< class T >
void Linked_list< T >::insert(const value_type &a, position p){
	position t = new List_node_ord<T>; // L'elemento verrà inserito in posizine p, nella nuova posizione t andrà invece un elemento già presente
	if(p==_pHead)
		_pHead = t;
	else
		t->_value = read(p);
	p->_value = a;
	t->_pNext = p->_pNext;
	t->_pPrev = p;
	p->_pNext->_pPrev = t;
	p->_pNext = t;

	_length++;
}

template< class T >
void Linked_list< T >::push_back(const value_type &a){
	insert(a,next(last()));
}

template< class T >
void Linked_list< T >::push_front(const value_type &a){
	insert(a,begin());
}

template< class T >
void Linked_list< T >::erase(position p){
	if (!empty() && !end(p)){
		p->_pPrev->_pNext = p->_pNext;
		p->_pNext->_pPrev = p->_pPrev;
		delete p;
		_length--;
	}
}


template<class T>
Linked_list<T>& Linked_list<T>::operator=(const Linked_list<T>& L){
	if (this != &L){
		_length = 0;

		_pHead = new List_node_ord<T>;
		_pHead->_pNext = _pHead;
		_pHead->_pPrev = _pHead;

		if (!L.empty()){
            position p = L.last();
			for (int i=0; i < L.size(); i++){
				insert(L.read(p), begin());
				p = L.previous(p);
			}
		}
	}
	return *this;
}

template<class T>
Linked_list<T>& Linked_list<T>::operator=(Linked_list<T>&& L){

	_length = 0;

	_pHead = new List_node_ord<T>;
	_pHead->_pNext = _pHead;
	_pHead->_pPrev = _pHead;

	if (!L.empty()){
        position p = L.last();
		for (int i=0; i < L.size(); i++){
			insert(L.read(p), begin());
			p = L.previous(p);
		}
	}
	while(!L.empty())
		erase(L.begin());
	return *this;
}

template<class T>
bool Linked_list<T>::operator==(const Linked_list<T> &L) const{
	if (L.size() != _length)
		return false;
	position p, pL;
	p = begin();
	pL = L.begin();
	while (!end(p)){
		if (p->_value == pL->_value) {
			p = p->_pNext;
			pL = pL->_pNext;
		}
		else
			return false;
	}
	return true;
}


#endif // _LINKED_LIST_H

