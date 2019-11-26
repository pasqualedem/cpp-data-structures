#ifndef _TREE_VECTOR_
#define _TREE_VECTOR_

#include "Tree.h"
#include <math.h>
#include "Tree_exceptions.h"
#include "Queue_linked.h"

template <class T>
class Tree_vector : public Tree<T, int >{
	public:
		typedef T value_type;
		typedef int node;
		Tree_vector(int);
		Tree_vector(int,int);
		Tree_vector(const Tree_vector&);
		~Tree_vector();
		
		void create();
		bool empty() const;
		node root() const;
		node parent(node) const;
		bool leaf(node) const;
		node fchild(node) const;
		bool has_child(node) const;
		bool lsibling(node) const;
		bool lnode_level(node u) const;
		node nsibling(node) const;
		void delete_sub(node);
		value_type read(node) const;
		void write(const value_type&, node);
		node insert_root ();
		node insert_root (const value_type&);
		node insert_child (node u);
		node insert_child (const value_type &,node u);
		void insert_first_sub_tree(node,const Tree_vector&); // insert a subtree where the sub tree is the first child of node
		void insert_sub_tree(node,const Tree_vector&); // insert a subtree where the sub tree is the next sibling of node
		void sub_tree(node, Tree_vector &) const;
		
		Tree_vector & operator= (const Tree_vector &);
		Tree_vector & operator= (Tree_vector &&);
		
		bool is_null (node) const ;
		node null_node() const;
		int size() { return _size;}
		
	private:
		T * SPACE;
		int dim_max;
		bool * qualified;
		bool * erased;
		int _size;
		int arity;
		
		static const int _null_node = -1;
		static const int _root_node = 0;
		void resize();
};

template<class T>
Tree_vector<T>::Tree_vector(int dim,int a) {
	dim_max = dim;	
	SPACE = new T[dim]; 
	qualified = new bool[dim];
	erased = new bool[dim];
	for (int i = 0; i < dim_max ; i++) {
		qualified[i] = false;
		erased[i] = false;
	}
	_size = 0;
	arity = a;
}

template<class T>
Tree_vector<T>::Tree_vector(int a) {
	dim_max = pow(a,5);	
	SPACE = new T[dim_max]; 
	qualified = new bool[dim_max];
	erased = new bool[dim_max];
	for (int i = 0; i < dim_max ; i++) {
		qualified[i] = false;
		erased[i] = false;
	}
	_size = 0;
	arity = a;
}

template<class T>
Tree_vector<T>::Tree_vector(const Tree_vector<T> & t) {
	dim_max = t.dim_max;	
	SPACE = new T[dim_max]; 
	erased = new bool[dim_max];
	qualified = new bool[dim_max];
	_size = t._size;
	arity = t.arity;
	for (int i = 0; i < dim_max ; i++) {
		if(t.qualified[i])
			SPACE[i] = t.SPACE[i];
		qualified[i] = t.qualified[i];
		erased[i] = t.erased[i];
	}
}

template<class T>
Tree_vector<T>::~Tree_vector() {
	delete[] SPACE; 
	delete[] qualified;
	delete[] erased;
}

template<class T>
void Tree_vector<T>::create() {
	_size = 0;
}

template<class T>
bool Tree_vector<T>::empty() const {
	return _size==0;
}

template<class T>
typename Tree_vector<T>::node Tree_vector<T>::root() const {
	return _root_node;
}

template<class T>
typename Tree_vector<T>::node Tree_vector<T>::parent(node u) const{
	return u/arity;
}

template<class T>
bool Tree_vector<T>::leaf(node u) const{
	return !has_child(u);
}

template<class T>
typename Tree_vector<T>::node Tree_vector<T>::fchild(node u) const{
	if(qualified[u]) {
		if( qualified[u*arity+1])
			return u*arity+1;
		else if( erased[u*arity+1] ) {
			int i = 0;
			node tmp = u*arity+1;
			while(erased[tmp+i] && !qualified[tmp+i] && i<arity+1) 
				i++;
			if(i>arity)
				return _null_node;
			else 
				return tmp+i;
		}
	return _null_node;
	}
	else
		return _null_node;
}


template<class T>
bool Tree_vector<T>::has_child(node u) const{
	if(qualified[u]) {
		if( qualified[u*arity+1])
			return true;
		else if( erased[u*arity+1] ) {
			int i = 0;
			node tmp = u*arity+1;
			while(erased[tmp+i] && !qualified[tmp+i] && i<arity+1) 
				i++;
			if(i>=arity)
				return false;
			else 
				return true;
		}
		return false;
	}
	else
		return false;
}

template<class T>
bool Tree_vector<T>::lsibling(node u) const {
	if(u%arity == 0)
		return true;
	if(!erased[u+1] && !qualified[u+1] )
		return true;
	else if (erased[u+1])
		return lsibling(u+1);
	else
		return false;
}

template<class T>
bool Tree_vector<T>::lnode_level(node u) const { // Last node of the level
	if( log2(u+1) - ((int)log2(u+1)) == 0 )
		return true;
	else
		return false;
}

template<class T>
typename Tree_vector<T>::node Tree_vector<T>::nsibling(node u) const {
	if(!lsibling(u) && !is_null(u))
		if(qualified[u+1])
			return u+1;
		else if ( erased[u+1] )
			return nsibling(u+1);
		else 
			return _null_node;
	else 
		return _null_node; //returns null node position 
}

template<class T>
void Tree_vector<T>::delete_sub(node u) {
	if(qualified[u]) {
		if(has_child(u)) {
			node tmp = fchild(u);
			node tmp_prec = tmp;
			while(!lsibling(tmp)) {
				tmp_prec = tmp;
				tmp = nsibling(tmp);
				delete_sub(tmp_prec);
			}
			delete_sub(tmp);
		}
		qualified[u] = false;
		erased[u] = true; 
		_size--;
	}
}


template<class T>
T Tree_vector<T>::read(node u) const {
	if(qualified[u])
		return SPACE[u];
	else 
		throw NodeNotExists();
}

template<class T>
void Tree_vector<T>::write(const T & v, node u) {
	if(qualified[u])
		SPACE[u] = v;
	else 
		throw NodeNotExists();
}

template<class T>
typename Tree_vector<T>::node Tree_vector<T>::insert_root() {
	if(!qualified[_root_node]) {
		qualified[_root_node] = true;
		_size = 1;
		return _root_node;
	}
	else {
		return _null_node;
	}
}

template<class T>
typename Tree_vector<T>::node Tree_vector<T>::insert_root(const T & v) {
	if(!qualified[_root_node]) {
		qualified[_root_node] = true;
		SPACE[_root_node] = v;
		_size = 1;
		return _root_node;
	}
	else {
		return _null_node;
	}
}

template<class T>
typename Tree_vector<T>::node Tree_vector<T>::insert_child(node u) {
	if((u*arity+1)*arity < dim_max-1 ) {
		node tmp;
		if(has_child(u)) {
			tmp = fchild(u);
			while(!lsibling(tmp) && !erased[tmp])
				tmp = nsibling(tmp);
			if(tmp%arity != 0) {
				tmp++;
				erased[tmp] = false;
				qualified[tmp] = true;
				_size++;
			}
			else 
				throw FullSize();
		}
		else {
			tmp = u*arity+1;
			erased[tmp] = false;
			qualified[tmp] = true;
			_size++;
		}
		return tmp;
	}
	else {
		resize();
		return insert_child(u);
	}
}

template<class T>
typename Tree_vector<T>::node Tree_vector<T>::insert_child(const T & v, node u) {
	if((u*arity+1)*arity < dim_max-1 ) {
		node tmp;
		if(has_child(u)) {
			tmp = fchild(u);
			while(!lsibling(tmp) && !erased[tmp])
				tmp = nsibling(tmp);
			if(tmp%arity != 0) {
				tmp++;
				erased[tmp] = false;
				qualified[tmp] = true;
				SPACE[tmp] = v;
				_size++;
			}
			else 
				throw FullSize();
		}
		else {
			tmp = u*arity+1;
			erased[tmp] = false;
			qualified[tmp] = true;
			SPACE[tmp] = v;
			_size++;
		}
		return tmp;	
	}
	else {
		resize();
		return insert_child(v,u);
	}
}

template<class T>
void Tree_vector<T>::insert_first_sub_tree(node u,const Tree_vector<T> & t) { 
	if(arity <= t.arity) 
		if(leaf(u)) {
			Queue_linked<node> q;
			Queue_linked<node> this_q;
			node tmp;
			node this_tmp;
			node father;
			node this_father;
			if(!t.empty()) {
				insert_child(t.read(t.root()), u);
				q.enqueue(t.root());
				this_q.enqueue(fchild(u));
			}
			while(!q.empty()) {
				tmp = q.front();
				this_tmp = this_q.front();
				q.dequeue();
				this_q.dequeue();
				if(!t.leaf(tmp)) {
					father = tmp;
					tmp = t.fchild(tmp);
					this_father = this_tmp;
					insert_child(t.read(tmp),this_father);
					this_tmp = fchild(this_father);
					this_q.enqueue(this_tmp);
					q.enqueue(tmp);
					while(!t.lsibling(tmp)) {
						tmp = t.nsibling(tmp);
						insert_child(t.read(tmp), this_father);
						this_tmp = nsibling(this_tmp);
						this_q.enqueue(this_tmp);
						q.enqueue(tmp);
					}
				}
			}
		}
		else
			throw NodeExists();
}


template<class T>
void Tree_vector<T>::insert_sub_tree(node u,const Tree_vector<T> & t) { 
	if(arity <= t.arity && u%arity != 0 && u!=_root_node) {
		u = parent(u);
		Queue_linked<node> q;
		Queue_linked<node> this_q;
		node tmp;
		node this_tmp;
		node father;
		node this_father;
		if(!t.empty()) {
			insert_child(t.read(t.root()), u);
			q.enqueue(t.root());
			this_tmp = fchild(u);
			while(!lsibling(this_tmp))
				this_tmp = nsibling(this_tmp);
			this_q.enqueue(this_tmp);
		}
		while(!q.empty()) {
			tmp = q.front();
			this_tmp = this_q.front();
			q.dequeue();
			this_q.dequeue();
			if(!t.leaf(tmp)) {
				father = tmp;
				tmp = t.fchild(tmp);
				this_father = this_tmp;
				insert_child(t.read(tmp),this_father);
				this_tmp = fchild(this_father);
				this_q.enqueue(this_tmp);
				q.enqueue(tmp);
				while(!t.lsibling(tmp)) {
					tmp = t.nsibling(tmp);
					insert_child(t.read(tmp), this_father);
					this_tmp = nsibling(this_tmp);
					this_q.enqueue(this_tmp);
					q.enqueue(tmp);
				}
			}
		}
	}
}

template<class T> 
void Tree_vector<T>::sub_tree(node u, Tree_vector<T> & t) const{ 
	t.delete_sub(t.root());
	if(!empty()) {
		t.insert_root(read(u));
		Queue_linked<node> sub_q;
		Queue_linked<node> q;
		node tmp;
		node sub_tmp;
		node sub_child;
		node this_child;
		q.enqueue(u);
		sub_q.enqueue(t.root());
		while(!q.empty()) {
			sub_tmp = sub_q.front();
			tmp = q.front();
			if(!leaf(tmp)) {
				this_child = fchild(tmp);
				t.insert_child(read(this_child), sub_tmp );
				sub_child = t.fchild(sub_tmp);
				sub_q.enqueue(sub_child);
				q.enqueue(this_child);
				this_child = nsibling(this_child);
				while(!is_null(this_child))  {// After is reached the last sibling, nsibling returns null node
					t.insert_child(read(this_child), sub_tmp );
					sub_child = t.nsibling (sub_child);
					sub_q.enqueue(sub_child);
					q.enqueue(this_child);
					this_child = nsibling (this_child);
				}
				
			}
			q.dequeue();
			sub_q.dequeue();		 
		}
	}
}

template<class T> 
bool Tree_vector<T>::is_null(node u) const{ 
	return u == _null_node;
}

template<class T> 
typename Tree_vector<T>::node Tree_vector<T>::null_node() const{ 
	return _null_node;
}

template<class T> 
void Tree_vector<T>::resize(){
	dim_max *= 2; 
	T * tmp_SPACE = new T[dim_max];
	bool * tmp_erased = new bool[dim_max];
	bool * tmp_qualified = new bool[dim_max];
	for(int i = 0;i<dim_max/2;i++) {
		tmp_SPACE[i] = SPACE[i];
		tmp_erased[i] = erased[i];
		tmp_qualified[i] = qualified[i];
	}
	for(int i = dim_max/2;i<dim_max;i++) {
		tmp_erased[i] = false;
		tmp_qualified[i] = false;
	}
	erased = tmp_erased;
	qualified = tmp_qualified;
	SPACE = tmp_SPACE;
}

template<class T>
Tree_vector<T> & Tree_vector<T>::operator= (const Tree_vector<T> & t) {
	if(this != &t) {
		dim_max = t.dim_max;	
		SPACE = new T[dim_max]; 
		erased = new bool[dim_max];
		qualified = new bool[dim_max];
		_size = t._size;
		arity = t.arity;
		for (int i = 0; i < dim_max ; i++) {
		if(t.qualified[i])
				SPACE[i] = t.SPACE[i];
			qualified[i] = t.qualified[i];
			erased[i] = t.erased[i];
		}
	}
	return *this;
}

template <class T>
Tree_vector<T> & Tree_vector<T>::operator= (Tree_vector && t) {
	dim_max = t.dim_max;	
	SPACE = new T[dim_max]; 
	erased = new bool[dim_max];
	qualified = new bool[dim_max];
	_size = t._size;
	arity = t.arity;
	for (int i = 0; i < dim_max ; i++) {
		if(t.qualified[i])
			SPACE[i] = t.SPACE[i];
		qualified[i] = t.qualified[i];
		erased[i] = t.erased[i];
	}
	return *this;
}

#endif


