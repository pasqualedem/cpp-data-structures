#ifndef _TREE_linked_
#define _TREE_linked_

#include "Tree.h"
#include <math.h>
#include "Tree_exceptions.h"
#include "Queue_linked.h"

template<class T>
class Tree_linked;

template <class T>
class Tree_node_linked {
	friend class Tree_linked<T>;
	private:
		T value;
		Tree_node_linked<T> * parent;
		Tree_node_linked<T> * fchild;
		Tree_node_linked<T> * nsibling;
	public:
		Tree_node_linked() {
			parent = 0x0;
			fchild = 0x0;
			nsibling = 0x0;
		}
		Tree_node_linked(T v) {
			parent = 0x0;
			fchild = 0x0;
			nsibling = 0x0;
			value = v;
		}
};

template <class T>
class Tree_linked : public Tree<T, Tree_node_linked<T> * >{
	public:
		typedef T value_type;
		typedef Tree_node_linked<T> * node;
		Tree_linked();
		Tree_linked(const Tree_linked&);
		Tree_linked(const Tree_linked&&);
		Tree_linked(T,hash_table<T,T>);
		~Tree_linked();
		
		void create();
		bool empty() const;
		node root() const;
		node parent(node) const;
		bool leaf(node) const;
		node fchild(node) const;
		bool lsibling(node) const;
		node nsibling(node) const;
		void delete_sub(node);
		value_type read(node) const;
		value_type & ref_read(node) const;
		void write(const value_type&, node);
		node insert_root ();
		node insert_root (const value_type&);
		node insert_child (node u);
		node insert_child (const value_type &,node u);
		void insert_first_sub_tree(node,const Tree_linked&); // insert a subtree where the sub tree is the first child of node
		void insert_last_sub_tree(node,const Tree_linked&); //insert a subtree where the sub tree is the last child of node, if node is leaf calls insert_first_sub_tree
		void insert_sub_tree(node,const Tree_linked&); // insert a subtree where the sub tree is the next sibling of node
		void sub_tree(node, Tree_linked &) const;
		
		Tree_linked & operator= (const Tree_linked &);
		Tree_linked & operator= (Tree_linked &&);
		bool operator== ( const Tree_linked &) const;
		
		bool is_null (node) const ;
		node null_node() const;
		int size() { return _size;}
		node psibling(node u) const;
		
	private:
		node _root;
		int _size;
		static const int _null_node = 0x0;
};

template<class T>
Tree_linked<T>::Tree_linked() {
	_root = 0x0;
	_size = 0;
}

template<class T>
Tree_linked<T>::Tree_linked(const Tree_linked<T> & t) {
	Queue_linked<node> q;
	Queue_linked<node> this_q;
	node tmp;
	node this_tmp;
	node father;
	node this_father;
	if(!t.empty()) {
		insert_root(t.read(t.root()));
		q.enqueue(t.root());
		this_q.enqueue(root());
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

template<class T>
Tree_linked<T>::Tree_linked(const Tree_linked<T> && t) {
	Queue_linked<node> q;
	Queue_linked<node> this_q;
	node tmp;
	node this_tmp;
	node father;
	node this_father;
	if(!t.empty()) {
		insert_root(t.read(t.root()));
		q.enqueue(t.root());
		this_q.enqueue(root());
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

template <class T>
Tree_linked<T>::Tree_linked(T r,hash_table<T,T> h) {
	Stack_linked<node> s;
	Linked_list<T> l;
	insert_root(r);
	s.push(root());
	typename Linked_list<T>::position pos;
	node father;
	while(!s.empty() && !h.empty()) {
		father = s.top();
		s.pop();
		l = h.keys(read(father));
		pos = l.begin();
		while(!l.end(pos)) {
			s.push(insert_child(l.read(pos),father));
			h.erase(l.read(pos));
			pos = l.next(pos);
		}
	}
}

template<class T>
Tree_linked<T>::~Tree_linked() {
	delete_sub(root());
}

template<class T>
void Tree_linked<T>::create() {
	_size = 0;
}

template<class T>
bool Tree_linked<T>::empty() const {
	return _size==0;
}

template<class T>
typename Tree_linked<T>::node Tree_linked<T>::root() const {
	return _root;
}

template<class T>
typename Tree_linked<T>::node Tree_linked<T>::parent(node u) const{
	return u->parent;
}

template<class T>
bool Tree_linked<T>::leaf(node u) const{
	return u->fchild == 0x0;
}

template<class T>
typename Tree_linked<T>::node Tree_linked<T>::fchild(node u) const{
	return u->fchild;
}

template<class T>
bool Tree_linked<T>::lsibling(node u) const {
	return u->nsibling == 0x0;
}

template<class T>
typename Tree_linked<T>::node Tree_linked<T>::nsibling(node u) const {
	return u->nsibling;
}

template<class T>
typename Tree_linked<T>::node Tree_linked<T>::psibling(node u) const {
	node tmp = 0x0;
	if(u!= _root && u->parent->fchild != u) {
		tmp = u->parent->fchild;
		while(tmp->nsibling != u)
			tmp = nsibling(tmp);
	}
	return tmp;
}

template<class T>
void Tree_linked<T>::delete_sub(node u) {
	if(!is_null(u)) {
		if(!leaf(u)) {
			node tmp = fchild(u);
			node tmp_prec = tmp;
			while(!lsibling(tmp)) {
				tmp_prec = tmp;
				tmp = nsibling(tmp);
				delete_sub(tmp_prec);
			}
			delete_sub(tmp);
		}
		if(u!= root()) {
			if(u->parent->fchild == u )
				u->parent->fchild = u->nsibling;
			else {
				node prec = psibling(u);
				prec->nsibling = nsibling(u);	
			}
		}
		else 
			_root = 0x0;
		delete u;
	_size--;
	}
}


template<class T>
T Tree_linked<T>::read(node u) const {
	return u->value;
}


template<class T>
T & Tree_linked<T>::ref_read(node u) const {
	return u->value;
}

template<class T>
void Tree_linked<T>::write(const T & v, node u) {
	u->value = v;
}

template<class T>
typename Tree_linked<T>::node Tree_linked<T>::insert_root() {
	_root = new Tree_node_linked<T>;
	_size = 1;
	return _root;
}

template<class T>
typename Tree_linked<T>::node Tree_linked<T>::insert_root(const T & v) {
	_root = new Tree_node_linked<T>(v);
	_size = 1;
	return _root;
}

template<class T>
typename Tree_linked<T>::node Tree_linked<T>::insert_child(node u) {
	node child = new Tree_node_linked<T>;
	child->parent = u; 
	_size++;
	if(leaf(u)) {
		u->fchild = child;
	}
	else {
		node tmp = fchild(u);
		while(!lsibling(tmp)) 
			tmp = nsibling(tmp);
		tmp->nsibling = child;
	}
	return child;
}

template<class T>
typename Tree_linked<T>::node Tree_linked<T>::insert_child(const T & v, node u) {
	node child = new Tree_node_linked<T>(v);
	child->parent = u; 
	_size++;
	if(leaf(u)) {
		u->fchild = child;
	}
	else {
		node tmp = fchild(u);
		while(!lsibling(tmp)) 
			tmp = nsibling(tmp);
		tmp->nsibling = child;
	}
	return child;
}

template<class T>
void Tree_linked<T>::insert_first_sub_tree(node u,const Tree_linked<T> & t) { 
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
}

template<class T>
void Tree_linked<T>::insert_last_sub_tree(node u,const Tree_linked<T> & t) { 
	if(!leaf(u)) {
		Queue_linked<node> q;
		Queue_linked<node> this_q;
		node tmp;
		node this_tmp;
		node father;
		node this_father;
		if(!t.empty()) {
			this_tmp = insert_child(t.read(t.root()), u);
			q.enqueue(t.root());
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
	else
		insert_first_sub_tree(u,t);
}

template<class T>
void Tree_linked<T>::insert_sub_tree(node u,const Tree_linked<T> & t) { 
	if(u!=root()) {
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
void Tree_linked<T>::sub_tree(node u, Tree_linked<T> & t) const{ 
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
Tree_linked<T> & Tree_linked<T>::operator= (const Tree_linked<T> & t) {
	delete_sub(root());
	Queue_linked<node> q;
	Queue_linked<node> this_q;
	node tmp;
	node this_tmp;
	node father;
	node this_father;
	if(!t.empty()) {
		insert_root(t.read(t.root()));
		q.enqueue(t.root());
		this_q.enqueue(root());
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
	return * this;
}

template <class T>
Tree_linked<T> & Tree_linked<T>::operator= (Tree_linked && t) {
	if(this != &t) {
		delete_sub(root());
		Queue_linked<node> q;
		Queue_linked<node> this_q;
		node tmp;
		node this_tmp;
		node father;
		node this_father;
		if(!t.empty()) {
			insert_root(t.read(t.root()));
			q.enqueue(t.root());
		this_q.enqueue(root());
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
	return * this;
}

template<class T> 
bool Tree_linked<T>::is_null(node u) const{ 
	return u == _null_node;
}

template<class T> 
typename Tree_linked<T>::node Tree_linked<T>::null_node() const{ 
	return (node)_null_node;
}

template<class T>
bool Tree_linked<T>::operator== (const Tree_linked<T> & t) const {
	Queue_linked<node> q;
	Queue_linked<node> this_q;
	node tmp;
	node this_tmp;
	node father;
	node this_father;
	if(_size != t._size)
		return false;
	if(!t.empty()) {
		q.enqueue(t.root());
		this_q.enqueue(root());
	}
	else
		return true;
	while(!q.empty()) {
		tmp = q.front();
		this_tmp = this_q.front();
		q.dequeue();
		this_q.dequeue();
		if(ref_read(this_tmp) != t.ref_read(tmp))
			return false;
		if(!t.leaf(tmp) && !leaf(this_tmp) ) {
			father = tmp;
			tmp = t.fchild(tmp);
			this_father = this_tmp;
			this_tmp = fchild(this_father);
			this_q.enqueue(this_tmp);
			q.enqueue(tmp);
			while(!t.lsibling(tmp) && !lsibling(this_tmp)) {
				tmp = t.nsibling(tmp);
				this_tmp = nsibling(this_tmp);
				this_q.enqueue(this_tmp);
				q.enqueue(tmp);
			}
			if( t.lsibling(tmp) ^ lsibling(this_tmp) )
				return false;
		}
		else if ( t.leaf(tmp) ^ leaf(this_tmp) )
			return false;
	}
	return true;
}

#endif


