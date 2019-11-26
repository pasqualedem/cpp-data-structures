#ifndef _BST_AVL_
#define _BST_AVL_

#include "Bintree.h"
#include "Queue_linked.h"
#include <iostream>

template<class K,class T>
class BST_AVL;

int Max(int a, int b) 
{ 
    return (a > b)? a : b; 
} 


template<class K,class T>
class AVL_node {
	friend class BST_AVL<K,T>;
	private:
		T value;
		K key;
		AVL_node * lcn; //lcn
		AVL_node * rcn; //rcn
		AVL_node * pn; //pn
		int h;
	public:
	int height()	{ 
    	return h;
	} 
};

template<class K,class T>
int node_height(AVL_node<K,T> * n ) {
	if(n == 0x0)
		return 0;
	else return n->height();
}

template<class K,class T>
class BST_AVL : public Bintree< T , AVL_node<K,T> * > {
	public:
		typedef T value_type;
		typedef typename Bintree<T, AVL_node<K,T> * >::node node;
		
		BST_AVL();
		BST_AVL(const BST_AVL&);
		~BST_AVL();
		//void build (node u,Bintree_linked &) ;
		void insert(const K & , const value_type &);
		void erase(const K & );
		void print() const;
	
		
		BST_AVL<K,T>& operator=( const BST_AVL<K,T>& );
		BST_AVL<K,T>& operator=( BST_AVL<K,T> && );
		bool operator==( const BST_AVL<K,T>& s) const;
		
		
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
		void delete_sub(node) ;
		BST_AVL & sub_tree(node, BST_AVL & ) const;
		value_type read(node) const ;
		K key(node) const ;
		void write(const value_type&, node) ;
		void build (BST_AVL &) ;
		void build (value_type , BST_AVL &) ;
		bool empty() const ;
		node root() const ;
		node parent(node) const ;
		node lchild(node) const ;
		node rchild(node) const ;
		bool lempty(node) const ;
		bool rempty(node) const ;
		bool leaf(node) const;
		node right_rotate(node);
		node left_rotate(node);
		void ins_balance(node,node);
		int get_balance(node) const;
		int sub_height(node) const;
		void sub_print(node) const;
		
};

template<class K,class T>
BST_AVL<K,T>::BST_AVL() {
	dim = 0;
	t_root = 0x0;
}

template<class K,class T>
BST_AVL<K,T>::BST_AVL(const BST_AVL<K,T> & b) {
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
BST_AVL<K,T>::~BST_AVL() {
	delete_sub(t_root);
	t_root = 0x0;
}

template<class K,class T>
bool BST_AVL<K,T>::empty() const {
	return dim == 0;
}

template<class K,class T>
typename BST_AVL<K,T>::node BST_AVL<K,T>::root() const {
	return t_root;
}

template<class K,class T>
typename BST_AVL<K,T>::node BST_AVL<K,T>::parent(node u) const {
	return u->pn;
}

template<class K,class T>
typename BST_AVL<K,T>::node BST_AVL<K,T>::lchild(node u) const {
	return u->lcn;
}

template<class K,class T>
typename BST_AVL<K,T>::node BST_AVL<K,T>::rchild(node u) const {
	return u->rcn;
}

template<class K,class T>
bool BST_AVL<K,T>::lempty(node u) const {
	return u->lcn == 0x0;
}

template<class K,class T>
bool BST_AVL<K,T>::rempty(node u) const {
	return u->rcn == 0x0;
}

template<class K,class T>
bool BST_AVL<K,T>::leaf(node u) const {
	return (rempty(u) && lempty(u));
}

template<class K,class T>
void BST_AVL<K,T>::build(BST_AVL<K,T> & b) {
	node tmp = new AVL_node<K,T>;
	tmp->pn=0x0;
	tmp->lcn = t_root;
	tmp->lcn = 0x0;
	dim++;
	t_root = tmp;
	if(!b.empty()) {
		Queue_linked<node> q;
		Queue_linked<node> this_q;
		insert_rchild(root(),b.read(b.root()));
		node tmp;
		node this_tmp;
		q.enqueue(b.root());
		this_q.enqueue(rchild(root()));
		while(!q.empty()) {
			tmp  = q.front();
			this_tmp = this_q.front();
			if(!b.lempty(tmp)) {
				insert_lchild(this_tmp,b.read(b.lchild(tmp))); 
				q.enqueue(b.lchild(tmp));
				this_q.enqueue(lchild(this_tmp));
			}
					if(!b.rempty(tmp)) {
				insert_rchild(this_tmp,b.read(b.rchild(tmp))); 
				q.enqueue(b.rchild(tmp));
				this_q.enqueue(rchild(this_tmp));
			}
			q.dequeue();
		}
	}
}
template<class K,class T>
void BST_AVL<K,T>::build(T v , BST_AVL<K,T> & b) {
	node tmp = new AVL_node<K,T>;
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
		insert_rchild(root(),b.read(b.root()));
		node tmp;
		node this_tmp;
		q.enqueue(b.root());
		this_q.enqueue(rchild(root()));
		while(!q.empty()) {
			tmp  = q.front();
			this_tmp = this_q.front();
			if(!b.lempty(tmp)) {
				insert_lchild(this_tmp,b.read(b.lchild(tmp))); 
				q.enqueue(b.lchild(tmp));
				this_q.enqueue(lchild(this_tmp));
			}
					if(!b.rempty(tmp)) {
				insert_rchild(this_tmp,b.read(b.rchild(tmp))); 
				q.enqueue(b.rchild(tmp));
				this_q.enqueue(rchild(this_tmp));
			}
			q.dequeue();
			this_q.dequeue();
		}
	}
}

template<class K,class T>
void BST_AVL<K,T>::delete_sub(node u) {
	if(u!= 0x0) {
		if(lempty(u) && rempty(u)) {
			if(u!=t_root){
				if(rchild(u->pn) == u )
					u->pn->rcn = 0x0;
				else
					u->pn->lcn = 0x0;
				}
			else
				t_root = 0x0; 
		} else {
		if(!lempty(u))
			delete_sub(lchild(u));
		}
		if(!rempty(u))
			delete_sub(rchild(u));
		delete u;
		dim--;
	}
}

template<class K,class T>
T BST_AVL<K,T>::read(node u) const {
	return u->value;
}	

template<class K,class T>
K BST_AVL<K,T>::key(node u) const {
	return u->key;
}	

template<class K,class T>
void BST_AVL<K,T>::write(const value_type & value ,node u) {
	u->value = value;
}	

template<class K,class T>
typename BST_AVL<K,T>::node BST_AVL<K,T>::insert_root () {
	if(empty()) {
		node u = new AVL_node<K,T>;
		u->pn = 0x0;
		u->lcn = 0x0;
		u->rcn = 0x0;
		u->h = 1;
		t_root = u;
		dim = 1;
		return u;
	}
	return 0x0;
}

template<class K,class T>
typename BST_AVL<K,T>::node BST_AVL<K,T>::insert_root (node u) {
	if(empty()) {
		t_root = u;
		dim = 1;
		return u;
	}
	return 0x0;
}

template<class K,class T>
typename BST_AVL<K,T>::node BST_AVL<K,T>::insert_root ( const T & v) {
	if(empty()) {
		node u = new AVL_node<K,T>;
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
typename BST_AVL<K,T>::node BST_AVL<K,T>::insert_root (const K & k,const T & v) {
	if(empty()) {
		node u = new AVL_node<K,T>;
		u->pn = 0x0;
		u->lcn = 0x0;
		u->rcn = 0x0;
		u->key = k;
		u->h= 1;
		t_root = u;
		dim = 1;
		u->value = v;
	}
}

template<class K,class T>
typename BST_AVL<K,T>::node BST_AVL<K,T>::insert_lchild (node u) {
	if(rempty(u)) {
		node n = new AVL_node<K,T>; 
		u->lcn = n;
		n->pn = u;
		n->lcn = 0x0;
		n->rcn = 0x0;
		n->h = 1;
		dim++;
		return n;
	}
	return 0x0;
}

template<class K,class T>
typename BST_AVL<K,T>::node BST_AVL<K,T>::insert_lchild (const T & v,node u) {
	if(lempty(u)) {
		node n = new AVL_node<K,T>; 
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
typename BST_AVL<K,T>::node BST_AVL<K,T>::insert_lchild (const K & k,const T & v,node u) {
	if(lempty(u)) {
		node n = new AVL_node<K,T>; 
		u->lcn = n;
		n->pn = u;
		n->lcn = 0x0;
		n->rcn = 0x0;
		n->value = v;
		n->key = k;
		n->h = 1;
		dim++;
		return n;
	}
	return 0x0;
}

template<class K,class T>
typename BST_AVL<K,T>::node BST_AVL<K,T>::insert_rchild (node u) {
	if(rempty(u)) {
		node n = new AVL_node<K,T>; 
		u->rcn = n;
		n->pn = u;
		n->lcn = 0x0;
		n->rcn = 0x0;
		n->h = 1;
		dim++;
		return n;
	}
	return 0x0;
}

template<class K,class T>
typename BST_AVL<K,T>::node BST_AVL<K,T>::insert_rchild (const T & v,node u) {
	if(rempty(u)) {
		node n = new AVL_node<K,T>; 
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
typename BST_AVL<K,T>::node BST_AVL<K,T>::insert_rchild (const K & k,const T & v,node u) {
	if(rempty(u)) {
		node n = new AVL_node<K,T>; 
		u->rcn = n;
		n->pn = u;
		n->lcn = 0x0;
		n->rcn = 0x0;
		n->value = v;
		n->key = k;
		n->h = 1;
		dim++;
		return n;
	}
	return 0x0;
}

template<class K,class T>
void BST_AVL<K,T>::insert(const K & k,const T & v) {
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
		u->h = max ( node_height(lchild(u)) , node_height(rchild(u)) ) + 1; 
		ins_balance(u,cur);
	}
}

template<class K,class T>
void BST_AVL<K,T>::erase(const K & k) {
}

template<class K,class T>
BST_AVL<K,T> & BST_AVL<K,T>::sub_tree(node u , BST_AVL<K,T> & sub) const {
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
BST_AVL<K,T>& BST_AVL<K,T>::operator=( const BST_AVL<K,T>&  b) {
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
BST_AVL<K,T>& BST_AVL<K,T>::operator=( BST_AVL<K,T> &&  b) {
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
bool  BST_AVL<K,T>::operator==( const BST_AVL<K,T> &  b) const{
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
			if(read(tmp) != b.read(this_tmp) || key(tmp) != b.key(this_tmp))
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
typename BST_AVL<K,T>::node  BST_AVL<K,T>::right_rotate( node u) { 
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
		u->h = max( node_height(u->lcn) ,  node_height(u->rcn) ) + 1;
		x->h = max( node_height(par->lcn) ,  node_height(par->rcn) ) + 1;
	}
	return x;
}

template<class K,class T>
typename BST_AVL<K,T>::node  BST_AVL<K,T>::left_rotate( node u) { 
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
	u->h = max( node_height(u->lcn) ,  node_height(u->rcn) ) + 1;
	x->h = max( node_height(x->lcn) ,  node_height(x->rcn) ) + 1;
	return x;
}

template<class K,class T>
void  BST_AVL<K,T>::ins_balance(node par,node u) { 
	int balance = get_balance(par);
	
	// Left Left Case 
	if(balance > 1 && key(u) < key(lchild(par)) )
		right_rotate(par);
    // Right Right Case 
    if (balance < -1 && key(u) > key(rchild(par))) 
    	left_rotate(par); 
  
    // Left Right Case 
    if (balance > 1 && key(u) > key(lchild(par))) { 
        par->lcn =  left_rotate(par->lcn); 
        right_rotate(par); 
    } 
  
    // Right Left Case 
    if (balance < -1 && key(u) < key(rchild(par))) { 
        par->rcn = right_rotate(par->rcn); 
        left_rotate(par); 
    } 
} 

template<class K,class T>
int  BST_AVL<K,T>::sub_height( node u) const { 
	int h = 0;
	if(u != 0x0)
		h =  max(sub_height( lchild(u) ),sub_height( rchild(u) ) );
	return h;
} 

template<class K,class T>
int  BST_AVL<K,T>::get_balance( node u) const{ 
	int h = 0;
	if(u != 0x0)
		h =  node_height( lchild(u) ) - node_height( rchild(u) ) ;
	return h;
} 

template<class K,class T>
void  BST_AVL<K,T>::print() const{ 
	cout<<"[ ";
	if(!empty())
		sub_print(root());
	cout<<" ]";
}

template<class K,class T>
void  BST_AVL<K,T>::sub_print(node u) const{ 
	if(!lempty(u)) {
		sub_print(lchild(u));
		cout<<", ";
	}
	cout<<key(u);
	if(!rempty(u)) {
		cout<<", ";
		sub_print(rchild(u));
	}
}


#endif
