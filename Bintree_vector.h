#ifndef _BINTREE_VECTOR_
#define _BINTREE_VECTOR_

#include "Bintree.h"
#include "Tree_exceptions.h"
#include "Queue_linked.h" 

template <class T>
class Bintree_vector : public Bintree<T, int >{
	public:
		typedef T value_type;
		typedef int node;
		Bintree_vector();
		Bintree_vector(int);
		Bintree_vector(const Bintree_vector&);
		~Bintree_vector();
		
		void create();
		bool empty() const;
		node root() const;
		node parent(node) const;
		bool leaf(node) const;
		node lchild(node) const;
		node rchild(node) const;	
		bool lempty(node) const;
		bool rempty(node) const;
		bool lnode_level(node u) const;
		void delete_sub(node);
		value_type read(node) const;
		void write(const value_type&, node);
		node insert_root ();
		node insert_root (const value_type&);
		node insert_lchild (node);
		node insert_rchild (node);
		node insert_lchild (const value_type &, node);
		node insert_rchild (const value_type &, node);
		void sub_Tree(node, Bintree_vector &) const;
		void build(const Bintree_vector &) ;
		void build(const value_type & v, const Bintree_vector &) ;
		Bintree_vector & sub_tree(node u , Bintree_vector<T> & sub) const; 
		
		Bintree_vector & operator= (const Bintree_vector &);
		Bintree_vector & operator= (Bintree_vector &&);
		bool operator== (const Bintree_vector &) const;
		
		bool null_node (node) const ;
		bool sub_equal (node u, node v,const Bintree_vector & t) const;
		bool isLeft(node) const;
		bool isRight(node) const;
		void left_shifting(node u = _root_node);
		void insert_lsub (const Bintree_vector &, node);
		void insert_rsub(const Bintree_vector &, node);
		int size() {return _size;}
		
	private:
		T * SPACE;
		int dim_max;
		bool * qualified;
		int _size;
		
		static const int _null_node = 0;
		static const int _root_node = 1;
		void resize();
};

template<class T>
Bintree_vector<T>::Bintree_vector(int dim) {
	if(dim<2) // 
		dim = 2;
	dim_max = dim;	
	SPACE = new T[dim]; 
	qualified = new bool[dim];
	for (int i = 0; i < dim_max ; i++) {
		qualified[i] = false;
	}
	_size = 0;
}

template<class T>
Bintree_vector<T>::Bintree_vector() {
	dim_max = 32;	
	SPACE = new T[dim_max]; 
	qualified = new bool[dim_max];
	for (int i = 0; i < dim_max ; i++) {
		qualified[i] = false;
	}
	_size = 0;
}

template<class T>
Bintree_vector<T>::Bintree_vector(const Bintree_vector<T> & t) {
	dim_max = t.dim_max;	
	SPACE = new T[dim_max]; 
	qualified = new bool[dim_max];
	size = t._size;
	for (int i = 0; i < dim_max ; i++) {
		if(t.qualified[i])
			SPACE[i] = t.SPACE[i];
		qualified[i] = t.qualified[i];
	}
}

template<class T>
Bintree_vector<T>::~Bintree_vector() {
	delete[] SPACE; 
	delete[] qualified;
}

template<class T>
void Bintree_vector<T>::create() {
	_size = 0;
}

template<class T>
bool Bintree_vector<T>::empty() const {
	return _size==0;
}

template<class T>
typename Bintree_vector<T>::node Bintree_vector<T>::root() const {
	return _root_node;
}

template<class T>
typename Bintree_vector<T>::node Bintree_vector<T>::parent(node u) const{
	return u/2;
}

template<class T>
bool Bintree_vector<T>::leaf(node u) const{
	return lempty(u) && rempty(u);
}

template<class T>
typename Bintree_vector<T>::node Bintree_vector<T>::lchild(node u) const{
	if(qualified[u]) {
		if( qualified[u*2])
			return u*2;
	return _null_node;
	}
}

template<class T>
typename Bintree_vector<T>::node Bintree_vector<T>::rchild(node u) const{
	if(qualified[u]) {
		if( qualified[u*2+1])
			return u*2+1;
	return _null_node;
	}
}

template<class T>
bool Bintree_vector<T>::lempty(node u) const{
	if(qualified[u]) {
		if( qualified[u*2])
			return false;
	return true;
	}
}

template<class T>
bool Bintree_vector<T>::rempty(node u) const{
	if(qualified[u]) {
		if( qualified[u*2+1])
			return false;
	return true;
	}
}

template<class T>
void Bintree_vector<T>::delete_sub(node u) {
	if(qualified[u]) {
		delete_sub(lchild(u)); //rchild and lchild will returns _null_node if don't exist, so delete_sub(0) will do nothing
		delete_sub(rchild(u)); 
		qualified[u] = false;
		_size--;
	}
}


template<class T>
T Bintree_vector<T>::read(node u) const {
	if(qualified[u])
		return SPACE[u];
	else 
		throw NodeNotExists();
}

template<class T>
void Bintree_vector<T>::write(const T & v, node u) {
	if(qualified[u])
		SPACE[u] = v;
	else 
		throw NodeNotExists();
}

template<class T>
typename Bintree_vector<T>::node Bintree_vector<T>::insert_root() {
	if(!qualified[_root_node]) {
		qualified[_root_node] = true;
		_size = 1;
		return _root_node;
	}
	else 
		return _null_node;
}

template<class T>
typename Bintree_vector<T>::node Bintree_vector<T>::insert_root(const T & v) {
	if(!qualified[_root_node]) {
		qualified[_root_node] = true;
		SPACE[_root_node] = v;
		_size = 1;
		return _root_node;
	}
	else 
		return _null_node;
}

template<class T>
typename Bintree_vector<T>::node Bintree_vector<T>::insert_lchild(node u) {
	if(u*4+1 < dim_max) {
		if(lempty(u)) {
			qualified[u*2] = true;
			_size++;
		}
		return u*2;
	}
	else {
		resize();
		return insert_lchild(u);
	}
}

template<class T>
typename Bintree_vector<T>::node Bintree_vector<T>::insert_lchild(const T & v,node u ) {
	if(u*4+1 < dim_max) {
		if(lempty(u)) {
			qualified[u*2] = true;
			_size++;
		}
		SPACE[u*2] = v;
		return u*2;	
	}
	else  {
		resize();
		return insert_lchild(u,v);
	}
}

template<class T>
typename Bintree_vector<T>::node Bintree_vector<T>::insert_rchild(node u) {
	if(u*4+1 < dim_max) {
		if(rempty(u)) {
			qualified[u*2+1] = true;
			_size++;
		}
		return u*2+1;
	}
	else  {
		resize();
		return insert_lchild(u);
	}
}

template<class T>
typename Bintree_vector<T>::node Bintree_vector<T>::insert_rchild(const T & v,node u) {
	if(u*4+1 < dim_max) {
		if(rempty(u)) {
			qualified[u*2+1] = true;
			_size++;
		}
		SPACE[u*2+1] = v;
		return u*2+1;
	}
	else  {
		resize();
		return insert_lchild(v,u);
	}
}

template <class T>
Bintree_vector<T> & Bintree_vector<T>::sub_tree(node u , Bintree_vector<T> & sub) const {
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
		sub.qualified[_root_node] = false;
	return sub;
}

template <class T>
void Bintree_vector<T>::build(const Bintree_vector<T> & sub) {
	left_shifting();
	insert_rsub(sub,root());
}

template <class T>
void Bintree_vector<T>::build(const T & v ,const Bintree_vector<T> & sub) {
	left_shifting();
	SPACE[_root_node] = v;
	insert_rsub(sub,root());
}

template <class T>
void Bintree_vector<T>::left_shifting(const node u ) {
	if(!leaf(u)) {
		if(!lempty(u))
			left_shifting(lchild(u));
		if(!rempty(u))
			left_shifting(rchild(u));
	}
	if(isRight(u)) {
		SPACE[(u-1)*2 + 1] = read(u);
		qualified[u] = false;
		qualified[(u-1)*2 + 1] = true;
	}
	else {
		insert_lchild(read(u),u);
	}
}

template<class T> 
bool Bintree_vector<T>::null_node(node u) const{ 
	return u == _null_node;
}

template<class T>
Bintree_vector<T> & Bintree_vector<T>::operator= (const Bintree_vector & t) {
	if(this != &t) {
		delete[] SPACE;
		delete[] qualified;
		dim_max = t.dim_max;	
		SPACE = new T[dim_max]; 
		qualified = new bool[dim_max];
		_size = t._size;
		for (int i = 0; i < dim_max ; i++) {
			if(t.qualified[i])
				SPACE[i] = t.SPACE[i];
			qualified[i] = t.qualified[i];
		}
	}
	return *this;
}

template<class T>
Bintree_vector<T> & Bintree_vector<T>::operator= (Bintree_vector && t) {
	delete[] SPACE;
	delete[] qualified;
	dim_max = t.dim_max;	
	SPACE = new T[dim_max]; 
	qualified = new bool[dim_max];
	_size = t._size;
	for (int i = 0; i < dim_max ; i++) {
		if(t.qualified[i])
			SPACE[i] = t.SPACE[i];
		qualified[i] = t.qualified[i];
	}
	return *this;
}

template<class T>
bool Bintree_vector<T>::operator== (const Bintree_vector & t) const {
	if(_size != t._size) 
		return false;
	if(empty())
		return true;
	if(read(root()) != t.read(t.root()))
		return false;
	if(!lempty(root()) && !t.lempty(t.root())) {
		if(! sub_equal(lchild(root()), t.lchild(t.root()) , t ) ) 
			return false;
		}
	else if ( lempty(root()) ^ t.lempty(t.root()) )
		return false;
	if(!rempty(root()) && !t.rempty(t.root())) {
		if(! sub_equal(lchild(root()), t.lchild(t.root() ), t) )
			return false;
		}
	else if ( rempty(root()) ^ t.rempty(t.root()) )
		return false;
	return true;
}

template<class T>
bool  Bintree_vector<T>::sub_equal (node u, node v,const Bintree_vector & t) const {
	if(read(u) != t.read(v))
		return false;
	if(!lempty(u)  && !t.lempty(v) ) {
		if(! sub_equal(lchild(u), t.lchild(v), t ) ) 
			return false;
		}
	else if ( lempty(u) ^ t.lempty(v) )
		return false;
	if(!rempty(u) && !t.rempty(v)) {
		if(! sub_equal(lchild(u), t.lchild(v), t) )
			return false;
		}
	else if ( rempty(u) ^ t.rempty(v) )
		return false;
	return true;
}

template<class T>
bool  Bintree_vector<T>::isLeft (node u) const {
	return (u%2 == 0 && u!=_root_node);
}

template<class T>
bool  Bintree_vector<T>::isRight (node u) const {
	return (u%2 != 0 && u!=_root_node);
}

template<class T>
void Bintree_vector<T>::insert_lsub (const Bintree_vector & t, node u) {
	if(qualified[u]) {
		if(!t.empty()) {
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
	else
		throw NodeNotExists();
}

template<class T>
void Bintree_vector<T>::insert_rsub (const Bintree_vector & t, node u) {
	if(qualified[u]) {
		if(!t.empty()) {
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
	else
		throw NodeNotExists();
}

template<class T> 
void Bintree_vector<T>::resize(){
	dim_max *= 2; 
	T * tmp_SPACE = new T[dim_max];
	bool * tmp_qualified = new bool[dim_max];
	for(int i = 0;i<dim_max/2;i++) {
		tmp_SPACE[i] = SPACE[i];
		tmp_qualified[i] = qualified[i];
	}
	for(int i = dim_max/2;i<dim_max;i++) {
		tmp_qualified[i] = false;
	}
	qualified = tmp_qualified;
	SPACE = tmp_SPACE;
}

#endif
