#ifndef _SET_LIST_
#define _SET_LIST_

#include "Set.h"
#include "Linked_list_ord.h"
#include <iostream>

template <class T> 
class Set_list : public Set<T> {
	public:
		typedef T value_type;
		
		Set_list();
		Set_list(Set_list<T> &);
		void create() ;
		bool empty() ;
		bool member(const value_type &) const ;
		void unity (const Set_list &) ;
		void intersection(const Set_list &) ;
		void erase (const value_type &) ;
		void add (const value_type &) ;
		void difference (const Set_list &) ;
		
		Set_list<T>& operator=( const Set_list<T>& sl);
		Set_list<T>& operator=(  Set_list<T>&& sl);
		value_type read() const;
		value_type & ref_read() const;
		bool  operator==( const Set_list<T>& sl) const;
		Set_list<T>& operator-( const Set_list<T>& sl);

		friend std::ostream& operator<<(std::ostream& os, Set_list<T> &sl){
		os<<sl.list;
		return os;
		}
		
	private:
		using Set<T>::_size;
		Linked_list_ord<T> list;
};

//Questi metodi hanno una scarsa efficienza derivata dalla composizione della classe con la lista ordinata, poichè possiamo utilizare solo i metodi della lista ordinata

template <class T>
Set_list<T>::Set_list() {
	_size = 0;
	
}


template <class T>
Set_list<T>::Set_list(Set_list<T> & sl) {
	_size = 0;
	typename Linked_list_ord<T>::position p_sl = sl.list.begin();
	while(!sl.list.end(p_sl)) {
		add(sl.list.read(p_sl));
		p_sl = sl.list.next(p_sl);
	}
}

template <class T>
void Set_list<T>::create() {
	_size = 0;
}

template <class T>
bool Set_list<T>::empty () {
	return _size==0;
}

template <class T>
bool Set_list<T>::member(const value_type & value) const {
	typename Linked_list_ord<T>::position p = list.begin();
	while(!(list.end(p)) && list.read(p) <= value) {
		if(value==list.read(p))
			return true;
		p = list.next(p);
	}
	return false;
}

template <class T> 
void Set_list<T>::unity(const Set_list & sl) {
	typename Linked_list_ord<T>::position p_sl = sl.list.begin();
	typename Linked_list_ord<T>::position p = list.begin();
	while(!sl.list.end(p_sl)) {
		add(sl.list.read(p_sl));
		p_sl = sl.list.next(p_sl);
	}
}


template <class T> 
void Set_list<T>::intersection(const Set_list & sl) { 
	typename Linked_list_ord<T>::position p = list.begin();
	typename Linked_list_ord<T>::position p_erase = list.begin();
	while(!list.end(p)) { 
		if(!sl.member(list.read(p))) {
			p_erase = p;
			p = list.next(p);
			erase(list.read(p_erase)); 
		}
		else
			p = list.next(p);
	}
}

template <class T>
void Set_list<T>::erase(const value_type & value) {
	typename Linked_list_ord<T>::position p = list.begin();
	while(!(list.end(p)) && list.read(p) <= value ) {
		if(value==list.read(p)) {
			list.erase(p);
			break;
		}
		p = list.next(p);
	}
	_size--;
}

template <class T>
void Set_list<T>::add(const value_type & value) {
	typename Linked_list_ord<T>::position p = list.begin();
	while(!(list.end(p)) && list.read(p) <= value ){
		if(value==list.read(p)) 
			return;
		p = list.next(p);
	}
	list.insert(value);
	_size++;
}

template <class T>
typename Set_list<T>::value_type Set_list<T>::read() const {
	return list.read(list.begin());
}

template <class T>
typename Set_list<T>::value_type & Set_list<T>::ref_read() const {
	return list.read(list.begin());
}

template <class T> 
void Set_list<T>::difference(const Set_list & sl) { 
	typename Linked_list_ord<T>::position p_sl = sl.list.begin();
	typename Linked_list_ord<T>::position p_sl_erase = sl.list.begin();
	while(!sl.list.end(p_sl)) {
		if(member(sl.list.read(p_sl))) {
			p_sl_erase = p_sl;
			p_sl = sl.list.next(p_sl);
			erase(sl.list.read(p_sl_erase));
			}
		else
			p_sl = sl.list.next(p_sl);
	}
}


template <class T> 
bool  Set_list<T>::operator==( const Set_list<T>& sl) const {
	if(_size!= sl._size)
		return false;
	
	if(list == sl.list)
		return true;
	else
		return false;
}

template <class T> 
Set_list<T>& Set_list<T>::operator-( const Set_list<T>& sl) {
	difference(sl);
	return *this;
}

template <class T> 
Set_list<T>& Set_list<T>::operator=( const Set_list<T>& sl) {
	if(this != &sl) {
		_size = sl.size;
		list = sl.list;
	}
	return *this;
}

template <class T> 
Set_list<T>& Set_list<T>::operator=( Set_list<T>&& sl) {
	_size = sl._size;
	list = sl.list;
	return *this;
}


#endif
