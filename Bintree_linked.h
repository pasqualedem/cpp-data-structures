#ifndef _BINALB_LINKED_
#define _BINALB_LINKED_

#include "Bintree.h"
#include "Queue_linked.h"
#include <iostream>

template<class T>
class Bintree_linked;

template<class T>
class Tree_node {
	friend class Bintree_linked<T>;
	private:
		T value;
		Tree_node * lcn; //lcn
		Tree_node * rcn; //rcn
		Tree_node * pn; //pn
};


template <class T>
class Bintree_linked : public Bintree< T , Tree_node<T> * > {
	public:
		typedef T value_type;
		typedef typename Bintree<T, Tree_node<T> * >::node node;
		
		Bintree_linked();
		Bintree_linked(const Bintree_linked&);
		~Bintree_linked();
		
		void create() ;
		bool empty() const ;
		node root() const ;
		node parent(node) const ;
		node lchild(node) const ;
		node rchild(node) const ;
		bool lempty(node) const ;
		bool rempty(node) const ;
		void build (Bintree_linked &) ;
		void build (value_type , Bintree_linked &) ;
		//void build (node u,Bintree_linked &) ;
		void delete_sub(node) ;
		value_type read(node) const ;
		value_type & ref_read(node) const ;
		void write(const value_type&, node) ;
		node insert_root () ;
		node insert_root (node) ;
		node insert_root (const value_type &); 
		node insert_lchild(node) ;
		node insert_lchild(const value_type&,node) ;
		node insert_rchild(node) ;
		node insert_rchild(const value_type&,node) ;
		Bintree_linked & sub_tree(node, Bintree_linked & ) const;
	
		
		Bintree_linked<T>& operator=( const Bintree_linked<T>& );
		Bintree_linked<T>& operator=( Bintree_linked<T> && );
		bool operator==( const Bintree_linked<T>& s) const;
		void right_rotate(node);
		void left_rotate(node);
		void insert_rsub(node u, const Bintree_linked<T> & b );
		void insert_lsub(node u, const Bintree_linked<T> & b );
		
		int size() const {return dim;}
		
	private:
		node t_root;
		int dim;
		
};

template <class T>
Bintree_linked<T>::Bintree_linked() {
	dim = 0;
	t_root = 0x0;
}

template <class T>
Bintree_linked<T>::Bintree_linked(const Bintree_linked<T> & b) {
	dim = 0;
	if(!b.empty()) {
		Queue_linked<node> q;
		Queue_linked<node> this_q;
		insert_root(b.read(b.root()));
		node tmp;
		node this_tmp;
		q.enqueue(b.root());
		this_q.enqueue(root());
		while(!q.empty()) {
			tmp  = q.front();
			this_tmp = this_q.front();
			if(!b.lempty(tmp)) {
				insert_lchild(b.read(b.lchild(tmp)), this_tmp); 
				q.enqueue(b.lchild(tmp));
				this_q.enqueue(lchild(this_tmp));
			}
					if(!b.rempty(tmp)) {
				insert_rchild(b.read(b.rchild(tmp)), this_tmp); 
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

template <class T>
Bintree_linked<T>::~Bintree_linked() {
	delete_sub(t_root);
	t_root = 0x0;
}

template <class T>
void Bintree_linked<T>::create() {
	t_root == 0x0;
	dim = 0;
}

template <class T>
bool Bintree_linked<T>::empty() const {
	return dim == 0;
}

template <class T>
typename Bintree_linked<T>::node Bintree_linked<T>::root() const {
	return t_root;
}

template <class T>
typename Bintree_linked<T>::node Bintree_linked<T>::parent(node u) const {
	return u->pn;
}

template <class T>
typename Bintree_linked<T>::node Bintree_linked<T>::lchild(node u) const {
	return u->lcn;
}

template <class T>
typename Bintree_linked<T>::node Bintree_linked<T>::rchild(node u) const {
	return u->rcn;
}

template <class T>
bool Bintree_linked<T>::lempty(node u) const {
	return u->lcn == 0x0;
}

template <class T>
bool Bintree_linked<T>::rempty(node u) const {
	return u->rcn == 0x0;
}

template <class T>
void Bintree_linked<T>::build(Bintree_linked<T> & b) {
	node tmp = new Tree_node<T>;
	tmp->pn=0x0;
	tmp->lcn = t_root;
	tmp->lcn = 0x0;
	dim++;
	t_root = tmp;
	if(!b.empty()) {
		Queue_linked<node> q;
		Queue_linked<node> this_q;
		insert_rchild(b.read(b.root()),root());
		node tmp;
		node this_tmp;
		q.enqueue(b.root());
		this_q.enqueue(rchild(root()));
		while(!q.empty()) {
			tmp  = q.front();
			this_tmp = this_q.front();
			if(!b.lempty(tmp)) {
				insert_lchild(b.read(b.lchild(tmp),this_tmp)); 
				q.enqueue(b.lchild(tmp));
				this_q.enqueue(lchild(this_tmp));
			}
					if(!b.rempty(tmp)) {
				insert_rchild(b.read(b.rchild(tmp)), this_tmp); 
				q.enqueue(b.rchild(tmp));
				this_q.enqueue(rchild(this_tmp));
			}
			q.dequeue();
			this_q.dequeue();
		}
	}
}
template <class T>
void Bintree_linked<T>::build(T v , Bintree_linked<T> & b) {
	node tmp = new Tree_node<T>;
	tmp->pn=0x0;
	tmp->lcn = t_root;
	tmp->rcn = 0x0;
	tmp->value = v;
	t_root->pn = tmp;
	dim++;
	t_root = tmp;
	if(!b.empty()) {
		Queue_linked<node> q;
		Queue_linked<node> this_q;
		insert_rchild(b.read(b.root()),root());
		node tmp;
		node this_tmp;
		q.enqueue(b.root());
		this_q.enqueue(rchild(root()));
		while(!q.empty()) {
			tmp  = q.front();
			this_tmp = this_q.front();
			if(!b.lempty(tmp)) {
				insert_lchild(b.read(b.lchild(tmp)),this_tmp); 
				q.enqueue(b.lchild(tmp));
				this_q.enqueue(lchild(this_tmp));
			}
					if(!b.rempty(tmp)) {
				insert_rchild(b.read(b.rchild(tmp)),this_tmp); 
				q.enqueue(b.rchild(tmp));
				this_q.enqueue(rchild(this_tmp));
			}
			q.dequeue();
			this_q.dequeue();
		}
	}
}

template <class T>
void Bintree_linked<T>::delete_sub(node u) {
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

template <class T>
T Bintree_linked<T>::read(node u) const {
	return u->value;
}	

template <class T>
T & Bintree_linked<T>::ref_read(node u) const {
	return u->value;
}	

template <class T>
void Bintree_linked<T>::write(const value_type & value ,node u) {
	u->value = value;
}	

template <class T>
typename Bintree_linked<T>::node Bintree_linked<T>::insert_root () {
	if(empty()) {
		node u = new Tree_node<T>;
		u->pn = 0x0;
		u->lcn = 0x0;
		u->rcn = 0x0;
		t_root = u;
		dim = 1;
		return u;
	}
	return 0x0;
}

template <class T>
typename Bintree_linked<T>::node Bintree_linked<T>::insert_root (node u) {
	if(empty()) {
		t_root = u;
		dim = 1;
		return u;
	}
	return 0x0;
}

template <class T>
typename Bintree_linked<T>::node Bintree_linked<T>::insert_root ( const T & v) {
	if(empty()) {
		node u = new Tree_node<T>;
		u->pn = 0x0;
		u->lcn = 0x0;
		u->rcn = 0x0;
		t_root = u;
		dim = 1;
		u->value = v;
	}
}

template <class T>
typename Bintree_linked<T>::node Bintree_linked<T>::insert_lchild (node u) {
	if(rempty(u)) {
		node n = new Tree_node<T>; 
		u->lcn = n;
		n->pn = u;
		n->lcn = 0x0;
		n->rcn = 0x0;
		dim++;
		return n;
	}
	return 0x0;
}

template <class T>
typename Bintree_linked<T>::node Bintree_linked<T>::insert_lchild (const T & v,node u) {
	if(lempty(u)) {
		node n = new Tree_node<T>; 
		u->lcn = n;
		n->pn = u;
		n->lcn = 0x0;
		n->rcn = 0x0;
		n->value = v;
		dim++;
		return n;
	}
	return 0x0;
}

template <class T>
typename Bintree_linked<T>::node Bintree_linked<T>::insert_rchild (node u) {
	if(rempty(u)) {
		node n = new Tree_node<T>; 
		u->rcn = n;
		n->pn = u;
		n->lcn = 0x0;
		n->rcn = 0x0;
		dim++;
		return n;
	}
	return 0x0;
}

template <class T>
typename Bintree_linked<T>::node Bintree_linked<T>::insert_rchild (const T & v,node u) {
	if(rempty(u)) {
		node n = new Tree_node<T>; 
		u->rcn = n;
		n->pn = u;
		n->lcn = 0x0;
		n->rcn = 0x0;
		n->value = v;
		dim++;
		return n;
	}
	return 0x0;
}

template <class T>
Bintree_linked<T> & Bintree_linked<T>::sub_tree(node u , Bintree_linked<T> & sub) const {
	sub.delete_sub(sub.root()); 
	if(!empty()) {
		Queue_linked<node> sub_q; //Coda che tiene traccia dell'albero da costruire
		Queue_linked<node> q; //Coda che tiene traccia dell'albero da scorrere
		sub.insert_root(read(u));
		node tmp;
		node sub_tmp;
		sub_q.enqueue(sub.root());
		q.enqueue(u);
		while(!q.empty()) {
			sub_tmp  = sub_q.front();
			tmp = q.front();
			if(!lempty(tmp)) {
				sub.insert_lchild(read(lchild(tmp)),sub_tmp); 
				sub_q.enqueue(lchild(sub_tmp));
				q.enqueue(lchild(tmp));
			}
			if(!rempty(tmp)) {
				sub.insert_rchild(read(rchild(tmp)),sub_tmp); 
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


template <class T>
Bintree_linked<T>& Bintree_linked<T>::operator=( const Bintree_linked<T>&  b) {
	if(this != &b) {
		delete_sub(t_root);
		dim = 0;
		if(!b.empty()) {
			Queue_linked<node> q;
			Queue_linked<node> this_q;
			insert_root(b.read(b.root()));
			node tmp;
			node this_tmp;
			q.enqueue(b.root());
				this_q.enqueue(root());
			while(!q.empty()) {
				tmp  = q.front();
				this_tmp = this_q.front();
					if(!b.lempty(tmp)) {
					insert_lchild(b.read(b.lchild(tmp)),this_tmp); 
					q.enqueue(b.lchild(tmp));
					this_q.enqueue(lchild(this_tmp));
				}
						if(!b.rempty(tmp)) {
						insert_rchild(b.read(b.rchild(tmp)),this_tmp); 
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
	return *this;
}

template <class T>
Bintree_linked<T>& Bintree_linked<T>::operator=( Bintree_linked<T> &&  b) {
	t_root = 0x0;
	dim = 0;
	if(!b.empty()) {
		Queue_linked<node> q;
		Queue_linked<node> this_q;
		insert_root(b.read(b.root()));
		node tmp;
		node this_tmp;
		q.enqueue(b.root());
		this_q.enqueue(root());
		while(!q.empty()) {
			tmp  = q.front();
			this_tmp = this_q.front();
			if(!b.lempty(tmp)) {
				insert_lchild(b.read(b.lchild(tmp)),this_tmp); 
				q.enqueue(b.lchild(tmp));
				this_q.enqueue(lchild(this_tmp));
			}
					if(!b.rempty(tmp)) {
				insert_rchild(b.read(b.rchild(tmp)),this_tmp); 
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

template <class T>
bool  Bintree_linked<T>::operator==( const Bintree_linked<T> &  b) const{
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
			if(read(tmp) != b.read(this_tmp) )
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

template <class T>
void  Bintree_linked<T>::right_rotate( node u) { 
	node x = lchild(u);
	if(x!= 0x0) {
		node y = rchild(x);
		node par = parent(u);
		u->lcn = y;
		if(y!= 0x0)
			y->pn = u;
		x->rcn = u;
		u->pn = x;
		if(par != 0x0) {
			if(par->lcn == u)
				par->lcn = x;
			else
				par->rcn = x;
		}
	}
}

template <class T>
void  Bintree_linked<T>::left_rotate( node u) { 
	node x = rchild(u);
	if(x!= 0x0) {
		node y = lchild(x);
		node par = parent(u);
		u->rcn = y;
		if(y!= 0x0)
			y->pn = u;
		x->lcn = u;
		u->pn = x;
		if(par != 0x0) {
			if(par->lcn == u)
				par->lcn = x;
			else
				par->rcn = x;
		}
	}
}

template<class T>
void Bintree_linked<T>::insert_rsub (node u,const Bintree_linked & t) {
	if(!t.empty() && rempty(u)) {
		Queue_linked<node> sub_q; //Coda che tiene traccia dell'albero da costruire
		Queue_linked<node> q; //Coda che tiene traccia dell'albero da scorrere
		insert_rchild(t.read(t.root()),u);
		node tmp;
		node sub_tmp;
		sub_q.enqueue(rchild(u));
		q.enqueue(t.root());
		while(!q.empty()) {
			sub_tmp  = sub_q.front();
			tmp = q.front();
			if(!t.lempty(tmp)) {
				insert_lchild(t.read(t.lchild(tmp)),sub_tmp); 
				sub_q.enqueue(lchild(sub_tmp));
				q.enqueue(t.lchild(tmp));
			}
			if(!t.rempty(tmp)) {
				insert_rchild(t.read(t.rchild(tmp)),sub_tmp); 
				sub_q.enqueue(rchild(sub_tmp));
				q.enqueue(t.rchild(tmp));
			}
			q.dequeue();
			sub_q.dequeue();
		}
	}
}

template<class T>
void Bintree_linked<T>::insert_lsub (node u,const Bintree_linked & t) {
	if(!t.empty() && lempty(u)) {
		Queue_linked<node> sub_q; //Coda che tiene traccia dell'albero da costruire
		Queue_linked<node> q; //Coda che tiene traccia dell'albero da scorrere
		insert_lchild(t.read(t.root()),u);
		node tmp;
		node sub_tmp;
		sub_q.enqueue(lchild(u));
		q.enqueue(t.root());
		while(!q.empty()) {
			sub_tmp  = sub_q.front();
			tmp = q.front();
			if(!t.lempty(tmp)) {
				insert_lchild(t.read(t.lchild(tmp)),sub_tmp); 
				sub_q.enqueue(lchild(sub_tmp));
				q.enqueue(t.lchild(tmp));
			}
			if(!t.rempty(tmp)) {
				insert_rchild(t.read(t.rchild(tmp)),sub_tmp); 
				sub_q.enqueue(rchild(sub_tmp));
				q.enqueue(t.rchild(tmp));
			}
			q.dequeue();
			sub_q.dequeue();
		}
	}
}

#endif
