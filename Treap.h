#ifndef _TREAP_
#define _TREAP_

#include <iostream>
#include <cstdlib>

template <class K,class E>
class Treap;

template <class K,class E>
class treapElement {
	friend class Treap<K,E>;
	K key;
	E value;
	long priority;
	
	public:
		treapElement (K k , E e) {
			key = k;
			value = e;
			priority = rand();
		}
		treapElement () {
		}
	bool operator<= (const treapElement & p) const {
		return key<=p.key;
	}
	bool operator< (const treapElement & p) const {
		return key<p.key;
	}
	bool operator>= (const treapElement & p) const {
		return key>=p.key;
	}
	bool operator> (const treapElement & p) const {
		return key>p.key;
	}
	bool operator== (const treapElement & p) const {
		if(key == p.key)
			if(value == p.value && priority == p.priority)
				return true;
		return false;
	}
	K getKey () {return  key;}
	E getValue () {return  value;}
	long getPriority () {return  priority;}
};

template <class K,class E>
class Treap {
	
	friend std::ostream& operator<<(std::ostream& out, const Treap<K,E> & p) {
		out<<"[ ";
   		for(int i = 1; i<=p.leaf;i++) {
   			out<<"<"<<p.tree[i].getKey()<<","<<p.tree[i].getValue()<<">";
   			if(i != p.leaf)
   				out<<", ";
		   }
		out<<" ]";
  		return out;
	}
	
	public:
		Treap();
		Treap(int);
		Treap(Treap &);
	    ~Treap();
	    
	    void insert(const treapElement<K,E> & e);
	    treapElement<K,E> min() const;
	    treapElement<K,E> max() const;
	    treapElement<K,E> erase(K);
	    
	    		
		Treap & operator= (const Treap &);
		Treap & operator= (Treap &&);
		bool operator== (const Treap &) const;
		bool 	equal (const Treap & p) const;
		
	private:
		treapElement<K,E> * tree; 
		int leaf;
		int dim_max;
		
		void fixUp(int);
		void fixDown(int);
		void swap (int,int);
		int greater (int,int) const;
		int lower (int,int) const;
		void resize ();
		bool equal_level (int level, const Treap & p) const;
};

template <class K,class E>
Treap<K,E>::Treap() {
	leaf = 0;
	dim_max = 100;
	tree = new treapElement<K,E>[dim_max]; 
}

template <class K,class E>
Treap<K,E>::Treap(int dim) {
	leaf = 0;
	dim_max = dim;
	tree = new treapElement<K,E>[dim_max]; 
}

template <class K,class E>
Treap<K,E>::~Treap() {
	delete[] tree;
}

template <class K,class E>
Treap<K,E>::Treap(Treap & p) {
	leaf = p.leaf;
	dim_max = p.dim_max;
	tree = new treapElement<K,E>[dim_max]; 
	for(int i = 0; i <= p.leaf; i++) {
		tree[i] = p.tree[i];
	}
}

template <class K,class E>
void Treap<K,E>::insert(const treapElement<K,E> & v) {
	if(leaf+1 < dim_max) {
		leaf++;
		tree[leaf] = v;
		fixUp(leaf);
	}
	else {
		resize();
		insert(v);
	}
}

template <class K,class E>
treapElement<K,E> Treap<K,E>::min() const {
	if(leaf > 0)
		return tree[1];
}

template <class K,class E>
treapElement<K,E> Treap<K,E>::erase() {
	fixDown(1);
	leaf--;
}

template <class K,class E>
void Treap<K,E>::fixUp(int node) {
	while(node>1 && tree[node] < tree[node/2] ) {
		swap(node,node/2);
		node /= 2;
	}
}

template <class K,class E>
void Treap<K,E>::fixDown(int node) {
	swap(node,leaf);
	int lwr;
	if(leaf>=node*2+1)
		lwr	= lower(node*2,node*2+1);
	else
		lwr = node*2;
	while(lwr<leaf && tree[node] > tree[lwr]) {
		swap(node,lwr);
		node = lwr;
		if(leaf>=node*2+1)
			lwr	= lower(node*2,node*2+1);
		else
			lwr = node*2;
	}
}

template <class K,class E>
int Treap<K,E>::greater(int a, int b)  const{
	if (tree[a]>tree[b])
		return a;
	else 
		return b;
}

template <class K,class E>
int Treap<K,E>::lower(int a, int b)  const{
	if (tree[a]<tree[b])
		return a;
	else 
		return b;
}

template <class K,class E>
void Treap<K,E>::swap(int a, int b) {
	treapElement<K,E> tmp;
	tmp = tree[a];
	tree[a] = tree[b];
	tree[b] = tmp;
}

template <class K,class E>
Treap<K,E> & Treap<K,E>::operator= (const Treap & p) {
	leaf = p.leaf;
	dim_max = p.dim_max;
	tree = new treapElement<K,E>[dim_max]; 
	for(int i = 0; i <= p.leaf; i++) {
		tree[i] = p.tree[i];
	}
}

template <class K,class E>
Treap<K,E> & Treap<K,E>::operator= (Treap && p) {
	leaf = p.leaf;
	dim_max = p.dim_max;
	tree = new treapElement<K,E>[dim_max]; 
	for(int i = 0; i <= p.leaf; i++) {
		tree[i] = p.tree[i];
	}
}

template <class K,class E>
bool Treap<K,E>::operator== (const Treap & p) const { 
	if(leaf != p.leaf)
		return false;
	for(int i = 1; i < leaf ;i*=2) {
		if(!equal_level(i,p));
			return false;
	}
	return true;
}

template <class K,class E>
bool Treap<K,E>::equal (const Treap & p) const {   // Two priority queues with binary true are equal if every level of the tree has the same values
	if(leaf != p.leaf)
		return false;
	for(int i = 1; i < leaf ;i*=2) {
		if(!equal_level(i,p))
			return false;
	}
	return true;
}

template <class K,class E>
bool Treap<K,E>::equal_level (int level, const Treap & p) const { 
	int last_node;
	if(level*2 > leaf)
		last_node = leaf;
	else
		last_node = level*2-1;
	bool found;
	for(int i = level; i <= last_node ;i++) {
		found = false;
		for(int j = level; j <= last_node && !found ;j++)
			if(tree[i] == p.tree[j])
				found = true;
		if(found)
			found = false;
		else 
			return false;
	}
	return true;
}

template <class K,class E>
void Treap<K,E>::resize () { 
	treapElement<K,E> * tmp = new treapElement<K,E>[dim_max*2];
	dim_max *= 2;
	for(int i = 1; i<=leaf ; i++) {
		tmp[i] = tree[i];
	}
	tree = tmp;
}

#endif
