#ifndef _BST_
#define _BST_

#include "Bintree.h"
#include "Queue_linked.h"
#include <iostream>

template<class K,class T>
class BST;

template<class K,class T>
class BST_node {
	friend class BST<K,T>;
	private:
		T value;
		K key;
		BST_node * lcn; //lcn
		BST_node * rcn; //rcn
		BST_node * pn; //pn
};

template<class K,class T>
class BST : public Bintree< T , BST_node<K,T> * > {
	public:
		typedef T value_type;
		typedef typename Bintree<T, BST_node<K,T> * >::node node;
		
		BST();
		BST(const BST&);
		~BST();
		void insert(const K & , const value_type &);
		void erase(const K & );
		void print() const;
		node find(const  K &) const;
		K next(const K &) const;
		K prev(const K &) const;
		K sub_min(const K & )const;
		K min () const;
		K sub_max(const K & )const;
		K max () const;
		T search(const K &) const;
		
		node _prev(const K &) const;
		node _next(const K &) const;
		node _sub_min(node) const;
		node _sub_max(node) const;
		node _min () const;
		node _max () const;
		
		BST<K,T>& operator=( const BST<K,T>& );
		BST<K,T>& operator=( BST<K,T> && );
		bool operator==( const BST<K,T>& s) const;
		
		void delete_sub(node) ;
		bool empty() const ;
		BST & sub_tree(node, BST & ) const;
		int size() const {return dim;}
		
	private:
		node t_root;
		int dim;
		
		void create() {}
		node insert_root () ;
		node insert_root (node) ;
		node insert_root (const value_type &); 
		node insert_root (const K& ,const value_type &); 
		node insert_lchild(node) ;
		node insert_lchild(const value_type&,node) ;
		node insert_lchild(const K& ,const value_type&,node) ;
		node insert_rchild(node) ;
		node insert_rchild(const value_type&,node) ;
		node insert_rchild(const K& ,const value_type&,node) ;
		value_type read(node) const ;
		K key(node) const ;
		void write(const value_type&, node) ;
		node root() const ;
		node parent(node) const ;
		node lchild(node) const ;
		node rchild(node) const ;
		bool lempty(node) const ;
		bool rempty(node) const ;
		bool leaf(node) const;
		void sub_print(node) const;
		
};

template<class K,class T>
BST<K,T>::BST() {
	dim = 0;
	t_root = 0x0;
}

template<class K,class T>
BST<K,T>::BST(const BST<K,T> & b) {
	dim = 0;
	if(!b.empty()) {
		Queue_linked<node> q;
		Queue_linked<node> this_q;
		insert_root(b.key(b.root()),b.read(b.root()));
		node tmp;
		node this_tmp;
		q.enqueue(b.root());
		this_q.enqueue(root());
		while(!q.empty()) {
			tmp  = q.front();
			this_tmp = this_q.front();
			if(!b.lempty(tmp)) {
				insert_lchild(b.key(b.lchild(tmp)),b.read(b.lchild(tmp)), this_tmp); 
				q.enqueue(b.lchild(tmp));
				this_q.enqueue(lchild(this_tmp));
			}
					if(!b.rempty(tmp)) {
				insert_rchild(b.key(b.rchild(tmp)),b.read(b.rchild(tmp)), this_tmp); 
				q.enqueue(b.rchild(tmp));
				this_q.enqueue(rchild(this_tmp));
			}
			q.dequeue();
			this_q.dequeue();
		}
	}
	else 
		t_root = 0;
}

template<class K,class T>
BST<K,T>::~BST() {
	delete_sub(t_root);
	t_root = 0x0;
}

template<class K,class T>
bool BST<K,T>::empty() const {
	return dim == 0;
}

template<class K,class T>
typename BST<K,T>::node BST<K,T>::root() const {
	return t_root;
}

template<class K,class T>
typename BST<K,T>::node BST<K,T>::parent(node u) const {
	return u->pn;
}

template<class K,class T>
typename BST<K,T>::node BST<K,T>::lchild(node u) const {
	return u->lcn;
}

template<class K,class T>
typename BST<K,T>::node BST<K,T>::rchild(node u) const {
	return u->rcn;
}

template<class K,class T>
bool BST<K,T>::lempty(node u) const {
	return u->lcn == 0x0;
}

template<class K,class T>
bool BST<K,T>::rempty(node u) const {
	return u->rcn == 0x0;
}

template<class K,class T>
bool BST<K,T>::leaf(node u) const {
	return (rempty(u) && lempty(u));
}


template<class K,class T>
void BST<K,T>::delete_sub(node u) {
	if(u!= 0x0) {
		if(u!=t_root){
			if(rchild(u->pn) == u )
				u->pn->rcn = 0x0;
			else
				u->pn->lcn = 0x0;
			}
		else
			t_root = 0x0; 
		if(!lempty(u))
			delete_sub(lchild(u));
		if(!rempty(u))
			delete_sub(rchild(u));
		delete u;
		dim--;
	}
}

template<class K,class T>
T BST<K,T>::read(node u) const {
	return u->value;
}	

template<class K,class T>
K BST<K,T>::key(node u) const {
	return u->key;
}	

template<class K,class T>
void BST<K,T>::write(const value_type & value ,node u) {
	u->value = value;
}	

template<class K,class T>
typename BST<K,T>::node BST<K,T>::insert_root () {
	if(empty()) {
		node u = new BST_node<K,T>;
		u->pn = 0x0;
		u->lcn = 0x0;
		u->rcn = 0x0;
		t_root = u;
		dim = 1;
		return u;
	}
	return 0x0;
}

template<class K,class T>
typename BST<K,T>::node BST<K,T>::insert_root (node u) {
	if(empty()) {
		t_root = u;
		dim = 1;
		return u;
	}
	return 0x0;
}

template<class K,class T>
typename BST<K,T>::node BST<K,T>::insert_root ( const T & v) {
	if(empty()) {
		node u = new BST_node<K,T>;
		u->pn = 0x0;
		u->lcn = 0x0;
		u->rcn = 0x0;
		u->height = 1;
		t_root = u;
		dim = 1;
		u->value = v;
	}
}

template<class K,class T>
typename BST<K,T>::node BST<K,T>::insert_root (const K & k,const T & v) {
	if(empty()) {
		node u = new BST_node<K,T>;
		u->pn = 0x0;
		u->lcn = 0x0;
		u->rcn = 0x0;
		u->key = k;
		t_root = u;
		dim = 1;
		u->value = v;
	}
}

template<class K,class T>
typename BST<K,T>::node BST<K,T>::insert_lchild (node u) {
	if(rempty(u)) {
		node n = new BST_node<K,T>; 
		u->lcn = n;
		n->pn = u;
		n->lcn = 0x0;
		n->rcn = 0x0;
		dim++;
		return n;
	}
	return 0x0;
}

template<class K,class T>
typename BST<K,T>::node BST<K,T>::insert_lchild (const T & v,node u) {
	if(lempty(u)) {
		node n = new BST_node<K,T>; 
		u->lcn = n;
		n->pn = u;
		n->lcn = 0x0;
		n->rcn = 0x0;
		n->value = v;
		n->height = 1;
		dim++;
		return n;
	}
	return 0x0;
}

template<class K,class T>
typename BST<K,T>::node BST<K,T>::insert_lchild (const K & k,const T & v,node u) {
	if(lempty(u)) {
		node n = new BST_node<K,T>; 
		u->lcn = n;
		n->pn = u;
		n->lcn = 0x0;
		n->rcn = 0x0;
		n->value = v;
		n->key = k;
		dim++;
		return n;
	}
	return 0x0;
}

template<class K,class T>
typename BST<K,T>::node BST<K,T>::insert_rchild (node u) {
	if(rempty(u)) {
		node n = new BST_node<K,T>; 
		u->rcn = n;
		n->pn = u;
		n->lcn = 0x0;
		n->rcn = 0x0;
		dim++;
		return n;
	}
	return 0x0;
}

template<class K,class T>
typename BST<K,T>::node BST<K,T>::insert_rchild (const T & v,node u) {
	if(rempty(u)) {
		node n = new BST_node<K,T>; 
		u->rcn = n;
		n->pn = u;
		n->lcn = 0x0;
		n->rcn = 0x0;
		n->value = v;
		n->height = 1;
		dim++;
		return n;
	}
	return 0x0;
}

template<class K,class T>
typename BST<K,T>::node BST<K,T>::insert_rchild (const K & k,const T & v,node u) {
	if(rempty(u)) {
		node n = new BST_node<K,T>; 
		u->rcn = n;
		n->pn = u;
		n->lcn = 0x0;
		n->rcn = 0x0;
		n->value = v;
		n->key = k;
		dim++;
		return n;
	}
	return 0x0;
}

template<class K,class T>
void BST<K,T>::insert(const K & k,const T & v) {
	if(find(k) == 0x0)
		if(empty()) {
			insert_root(k,v);
		}
		else {			
			bool done = false;
			node u = root();
			node cur;
			while(!leaf(u)) {
					if( k < key(u) ) {
					if(!lempty(u))
						u = lchild(u);
					else {
						cur = insert_lchild(k,v,u);
						done = true;
							break;
					}
					
				}
				else {
					if(!rempty(u))
						u = rchild(u);
					else {
						cur = insert_rchild(k,v,u);
						done = true;
						break;
					}
				}
			}
			if(!done) {
				if(k < key(u))
					cur = insert_lchild(k,v,u);
				else 
					cur = insert_rchild(k,v,u);
			}
		}
}

template<class K,class T>
typename BST<K,T>::node BST<K,T>::find(const K & k) const{
	if(empty())
		return 0x0;
	node u = root();
	bool end = false;
	while(!end && k!= key(u))
		if(k<key(u))
			if(!lempty(u))
				u = lchild(u);
			else
				end = true;
		else 
			if(!rempty(u))
				u = rchild(u);
			else
				end = true;
	if(k == key(u))
		return u;
	else
		return 0x0;
}

template<class K,class T>
T BST<K,T>::search(const K & k) const{
	node u =find(k);
	if(u != 0x0)
		return read(u);
}

template<class K,class T>
K BST<K,T>::next(const K & k) const{
	node u = find(k);
	if(u != 0x0) {
		if(u->lcn != 0)
			return key(_sub_min(u->rcn));
		else{
			while(u->pn != 0x0 && u->pn->rcn == u)
				u = u->pn;
			if(u->pn == 0x0)
				return key(u);
			else
				return key(u->pn);
			}
	}
}

template<class K,class T>
typename BST<K,T>::node BST<K,T>::_next(const K & k) const{
	node u = find(k);
	if(u != 0x0) {
		if(u->lcn != 0)
			return _sub_min(u->rcn);
		else{
			while(u->pn != 0x0 && u->pn->rcn == u)
				u = u->pn;
			if(u->pn == 0x0)
				return u;
			else
				return u->pn;
			}
	}
}

template<class K,class T>
K BST<K,T>::prev(const K & k) const{
	node u = find(k);
	if(u != 0x0) {
		if(u->rcn != 0)
			return key(_sub_max(u->rcn));
		else{
			while(u->pn != 0x0 && u->pn->lcn == u)
				u = u->pn;
			if(u->pn == 0x0)
				return key(u);
			else
				return key(u->pn);
			}
	}
}

template<class K,class T>
typename BST<K,T>::node BST<K,T>::_prev(const K & k) const{
	node u = find(k);
	if(u != 0x0) {
		if(u->rcn != 0)
			return _sub_max(u->rcn);
		else{
			while(u->pn != 0x0 && u->pn->lcn == u)
				u = u->pn;
			if(u->pn == 0x0)
				return u;
			else
				return u->pn;
			}
	}
}

template<class K,class T>
void BST<K,T>::erase(const K & k) {
	node u = find(k);
	if(u != 0x0){
		if(leaf(u))
			delete_sub(u);
		else {
			node y;
			if(lempty(u)) {
				y = rchild(u);
			}
			else if(rempty(u)) {
				y = lchild(u);
			}
			else {
				y = _next(key(u));
				if(u->rcn == y) {
					if(!lempty(u)) {
						node l = lchild(u);
						l->pn = y;
							y->lcn = l;
					}
				}
				else {
					node r = rchild(u);
					node x = rchild(y);
					node l = lchild(u);
					node p = parent(y);
					y->rcn = r;
					r->pn = y;
					p->lcn = x;
					if(x!= 0x0)
						x->pn = p;
					y->lcn = l;
					if(l!= 0x0)
						l->pn = y;
				}
			}
			y->pn = u->pn;
			if(y->pn != 0x0) {
				if(u->pn->lcn == u)
					u->pn->lcn = y;
				else
					u->pn->rcn = y;
			}
			else
				t_root = y;
			delete(u);	
			dim--;
		}
	}
}

template<class K,class T>
BST<K,T> & BST<K,T>::sub_tree(node u , BST<K,T> & sub) const {
	sub.delete_sub(sub.root()); 
	if(!empty()) {
		Queue_linked<node> sub_q; //Coda che tiene traccia dell'albero da costruire
		Queue_linked<node> q; //Coda che tiene traccia dell'albero da scorrere
		sub.insert_root(key(u),read(u));
		node tmp;
		node sub_tmp;
		sub_q.enqueue(sub.root());
		q.enqueue(u);
		while(!q.empty()) {
			sub_tmp  = sub_q.front();
			tmp = q.front();
			if(!lempty(tmp)) {
				sub.insert_lchild(key(lchild(tmp)),read(lchild(tmp)),sub_tmp); 
				sub_q.enqueue(lchild(sub_tmp));
				q.enqueue(lchild(tmp));
			}
			if(!rempty(tmp)) {
				sub.insert_rchild(key(rchild(tmp)),read(rchild(tmp)),sub_tmp); 
				sub_q.enqueue(rchild(sub_tmp));
				q.enqueue(rchild(tmp));
			}
			q.dequeue();
			sub_q.dequeue();
		}
	}
	else 
		sub.t_root = 0;
	return sub;
}


template<class K,class T>
BST<K,T>& BST<K,T>::operator=( const BST<K,T>&  b) {
	delete_sub(t_root);
	dim = 0;
	if(!b.empty()) {
		Queue_linked<node> q;
		Queue_linked<node> this_q;
		insert_root(b.key(b.root()),b.read(b.root()));
		node tmp;
		node this_tmp;
		q.enqueue(b.root());
		this_q.enqueue(root());
		while(!q.empty()) {
			tmp  = q.front();
			this_tmp = this_q.front();
			if(!b.lempty(tmp)) {
				insert_lchild(b.key(b.lchild(tmp)),b.read(b.lchild(tmp)),this_tmp); 
				q.enqueue(b.lchild(tmp));
				this_q.enqueue(lchild(this_tmp));
			}
					if(!b.rempty(tmp)) {
				insert_rchild(b.key(b.rchild(tmp)),b.read(b.rchild(tmp)),this_tmp); 
				q.enqueue(b.rchild(tmp));
				this_q.enqueue(rchild(this_tmp));
			}
			q.dequeue();
			this_q.dequeue();
		}
	}
	else 
		t_root = 0;
	return *this;
}

template<class K,class T>
BST<K,T>& BST<K,T>::operator=( BST<K,T> &&  b) {
	t_root = 0x0;
	dim = 0;
	if(!b.empty()) {
		Queue_linked<node> q;
		Queue_linked<node> this_q;
		insert_root(b.key(b.root()),b.read(b.root()));
		node tmp;
		node this_tmp;
		q.enqueue(b.root());
		this_q.enqueue(root());
		while(!q.empty()) {
			tmp  = q.front();
			this_tmp = this_q.front();
			if(!b.lempty(tmp)) {
				insert_lchild(b.key(b.lchild(tmp)),b.read(b.lchild(tmp)),this_tmp); 
				q.enqueue(b.lchild(tmp));
				this_q.enqueue(lchild(this_tmp));
			}
					if(!b.rempty(tmp)) {
				insert_rchild(b.key(b.rchild(tmp)),b.read(b.rchild(tmp)),this_tmp); 
				q.enqueue(b.rchild(tmp));
				this_q.enqueue(rchild(this_tmp));
			}
			q.dequeue();
			this_q.dequeue();
		}
	}
	else 
		t_root = 0;
	return *this;
}

template<class K,class T>
bool  BST<K,T>::operator==( const BST<K,T> &  b) const{
	if(dim == b.dim)
	if(!b.empty() && !empty()) {
		Queue_linked<node> q;
		Queue_linked<node> this_q;
		node tmp;
		node this_tmp;
		q.enqueue(b.root());
		this_q.enqueue(root());
		while(!q.empty()) {
			tmp  = q.front();
			this_tmp = this_q.front();
			if(read(tmp) != b.read(this_tmp) || key(tmp) != b.key(this_tmp) )
				return false; // Nodes have different values
				
			if(!b.lempty(tmp) && !lempty(this_tmp)) {
				q.enqueue(b.lchild(tmp));
				this_q.enqueue(lchild(this_tmp));
			} else if ( !(b.lempty(tmp) && lempty(this_tmp)) )
				return false; // Tree structures id different 
				
			if(!b.rempty(tmp) && !rempty(this_tmp)) {
				q.enqueue(b.rchild(tmp));
				this_q.enqueue(rchild(this_tmp));
			} else if ( !(b.rempty(tmp) && rempty(this_tmp)) )
				return false; // Tree structures id different 
			this_q.dequeue();
			q.dequeue();
		}
		return true;
	}
	else if(b.empty() && empty())
			return true;
		else 
			return false;
	else 
		return false;
}

template<class K,class T>
void  BST<K,T>::print() const{ 
	cout<<"[ ";
	if(!empty())
		sub_print(root());
	cout<<" ]";
}

template<class K,class T>
void  BST<K,T>::sub_print(node u) const{ 
	if(!lempty(u)) {
		sub_print(lchild(u));
		cout<<", ";
	}
	cout<<"("<<key(u)<<","<<read(u)<<")";
	if(!rempty(u)) {
		cout<<", ";
		sub_print(rchild(u));
	}
}

template<class K,class T>
typename BST<K,T>::node BST<K,T>::_sub_min(node u) const{ 
	if(lempty(u))
		return u;
	else
		return _sub_min(lchild(u));
}

template<class K,class T>
typename BST<K,T>::node BST<K,T>::_min() const{ 
	if(!empty()) {
		if(lempty(root()))
			return root();
		else
			return _sub_min(lchild(root()));
	}
}

template<class K,class T>
K BST<K,T>::sub_min(const K & k) const{ 
	node u = find(k);
	if(u != 0x0)
		return key(_sub_min(u));
}

template<class K,class T>
K BST<K,T>::min() const{ 
	if(!empty()) {
		if(lempty(root()))
			return key(root());
		else
			return key(_sub_min(lchild(root())));
	}
}

template<class K,class T>
typename BST<K,T>::node BST<K,T>::_sub_max(node u) const{ 
	if(rempty(u))
		return u;
	else
		return _sub_max(rchild(u));
}

template<class K,class T>
typename BST<K,T>::node BST<K,T>::_max() const{ 
	if(!empty()) {
		if(rempty(root()))
			return root();
		else
			return _sub_max(rchild(root()));
	}
}

template<class K,class T>
K BST<K,T>::sub_max(const K & k) const{ 
	node u = find(k);
	if(u != 0x0)
		return key(_sub_max(u));
}

template<class K,class T>
K BST<K,T>::max() const{ 
	if(!empty()) {
		if(rempty(root()))
			return key(root());
		else
			return key(_sub_max(rchild(root())));
	}
}

#endif
