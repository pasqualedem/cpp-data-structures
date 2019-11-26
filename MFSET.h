#ifndef _MFSET_
#define _MFSET_

#include "Set.h"
#include "Linked_list_ord.h"
#include "Tree_linked.h"
#include <iostream>

template <class T> 
class MFSET {
	public:
		typedef T value_type;
		typedef Tree_linked<T> com_element;
		typedef typename Linked_list<com_element>::position component;
		MFSET();
		MFSET(const Set_list<T>);
		MFSET(MFSET<T> &);
		void create() ;
		bool empty() ;
		bool find(const value_type &, component) const ;
		bool same_component(const value_type &, const value_type &) const;
		void merge(const value_type &, const value_type &);
		
		
		Linked_list< component > components() const;
		value_type & read(component) const;
		Set_list<T> read_component(component) const;
		component search(const value_type &) const ;
		bool  operator==( const MFSET<T>& sl) const;

		friend std::ostream& operator<<(std::ostream& out, const MFSET<T> & m) {
			out<<"[ ";
			component c = m._components.begin() ;
   			while( !m._components.end(c) ) {
   				m._components.read(c).BFS(out);
   				c = m._components.next(c);
   				if(!m._components.end(c))
   					out<<", ";
			   }
			out<<" ]";
  			return out;
		}
		
	private:
		Linked_list< com_element > _components;
		int _size;
};

template <class T>
MFSET<T>::MFSET(Set_list<T> s) {
	T el;
	while(!s.empty()) {
		el = s.read();
		com_element tmp;
		tmp.insert_root(el);
		s.erase(el);
		_components.push_back( tmp );
		_size++;
	}
	
}

template <class T>
MFSET<T>::MFSET() {
	_size = 0;
}

template <class T>
MFSET<T>::MFSET(MFSET<T> & m) {
	_size = m._size;
	_components = m._components;
}

template <class T>
bool MFSET<T>::empty () {
	return _size==0;
}

template <class T>
bool MFSET<T>::find(const value_type & x, component y) const {
	com_element & c = components.ref_read(y);
	return c.find(x); 	
}

template <class T>
void MFSET<T>::merge( const value_type & x, const value_type & y)  {
	component cx = _components.begin();
	component cy = _components.begin();
	while(!_components.ref_read(cx).find(x) && !_components.end(cx) )
		cx = _components.next(cx);
	if(_components.end(cx))
		return;
	while(!_components.ref_read(cy).find(y) && !_components.end(cy) )
		cy = _components.next(cy);
	if(_components.end(cy))
		return;
	_components.ref_read(cx).insert_last_sub_tree(_components.ref_read(cx).root() , _components.ref_read(cy)  );
	_components.erase(cy);
}

template <class T>
bool MFSET<T>::same_component( const value_type & x, const value_type & y) const {
	component cx = _components.begin();
	component cy = _components.begin();
	while(!_components.read(cx).find(x) && !_components.end(cx) )
		cx = _components.next(cx);
	if(_components.end(cx))
		return false;
	while(!_components.read(cy).find(y) && !_components.end(cy) )
		cy = _components.next(cy);
	if(_components.end(cy))
		return false;
	return cx == cy;
}

template <class T>
typename MFSET<T>::component MFSET<T>::search( const value_type & x) const {
	component cx = _components.begin();
	while(!_components.read(cx).find(x) && 	!_components.end(cx) )
		cx = _components.next(cx);
	if(_components.end(cx))
		return 0x0;
	else
		return cx;
}


template <class T>
typename MFSET<T>::value_type & MFSET<T>::read(component c) const {
	return components.ref_read(c).root();
}

template <class T>
Set_list<T> MFSET<T>::read_component(component c) const {
	Set_list<T> s;
	_components.read(c).toSet(s);
	return s;
}


template <class T>
Linked_list< typename MFSET<T>::component > MFSET<T>::components() const {
	Linked_list< component > c;
	component pos = _components.begin();
	while(!_components.end(pos)) {
		c.push_back(pos);
		_components.next(pos);
	}
	return c;
}

template <class T> 
bool  MFSET<T>::operator==( const MFSET<T>& m) const {
	if(_size!= m._size)
		return false;
	
	if(components == m.components)
		return true;
	else
		return false;
}

#endif
