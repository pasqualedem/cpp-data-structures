#ifndef _PRIORITYQ_BIN_
#define _PRIORITYQ_BIN_

#include <iostream>

template <class K,class E>
class PriorityQ_heap;

template <class K,class E>
class priorElement {
	friend class PriorityQ_heap<K,E>;
	K key;
	E value;
	
	public:
		priorElement (K k , E e) {
			key = k;
			value = e;
		}
		priorElement () {
		}
	bool operator<= (const priorElement & p) const {
		return key<=p.key;
	}
	bool operator< (const priorElement & p) const {
		return key<p.key;
	}
	bool operator>= (const priorElement & p) const {
		return key>=p.key;
	}
	bool operator> (const priorElement & p) const {
		return key>p.key;
	}
	bool operator== (const priorElement & p) const {
		if(key == p.key)
			if(value == p.value)
				return true;
		return false;
	}
	K getKey () const {return  key;}
	E getValue () const {return  value;}
	
	friend std::ostream& operator<<(std::ostream& out, const priorElement<K,E> & p) {
		out<<"<"<<p.getKey()<<","<<p.getValue()<<">";
  		return out;
	}
};

template <class K,class E>
class PriorityQ_heap {
	
	friend std::ostream& operator<<(std::ostream& out, const PriorityQ_heap<K,E> & p) {
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
		PriorityQ_heap();
		PriorityQ_heap(int);
		PriorityQ_heap(PriorityQ_heap &);
	    ~PriorityQ_heap();
	    
	    void insert(const priorElement<K,E> & e);
	    priorElement<K,E> min() const;
	    priorElement<K,E> erase();
	    bool empty() const;
	    		
		PriorityQ_heap & operator= (const PriorityQ_heap &);
		PriorityQ_heap & operator= (PriorityQ_heap &&);
		bool operator== (const PriorityQ_heap &) const;
		bool 	equal (const PriorityQ_heap & p) const;
		
	private:
		priorElement<K,E> * tree; 
		int leaf;
		int dim_max;
		
		void fixUp(int);
		void fixDown(int);
		void swap (int,int);
		int greater (int,int) const;
		int lower (int,int) const;
		void resize ();
		bool equal_level (int level, const PriorityQ_heap & p) const;
};

template <class K,class E>
PriorityQ_heap<K,E>::PriorityQ_heap() {
	leaf = 0;
	dim_max = 100;
	tree = new priorElement<K,E>[dim_max]; 
}

template <class K,class E>
PriorityQ_heap<K,E>::PriorityQ_heap(int dim) {
	leaf = 0;
	dim_max = dim;
	tree = new priorElement<K,E>[dim_max]; 
}

template <class K,class E>
PriorityQ_heap<K,E>::~PriorityQ_heap() {
	delete[] tree;
}

template <class K,class E>
PriorityQ_heap<K,E>::PriorityQ_heap(PriorityQ_heap & p) {
	leaf = p.leaf;
	dim_max = p.dim_max;
	tree = new priorElement<K,E>[dim_max]; 
	for(int i = 0; i <= p.leaf; i++) {
		tree[i] = p.tree[i];
	}
}

template <class K,class E>
bool PriorityQ_heap<K,E>::empty() const {
	return leaf==0;
}

template <class K,class E>
void PriorityQ_heap<K,E>::insert(const priorElement<K,E> & v) {
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
priorElement<K,E> PriorityQ_heap<K,E>::min() const {
	if(leaf > 0)
		return tree[1];
}

template <class K,class E>
priorElement<K,E> PriorityQ_heap<K,E>::erase() {
	fixDown(1);
	leaf--;
}

template <class K,class E>
void PriorityQ_heap<K,E>::fixUp(int node) {
	while(node>1 && tree[node] < tree[node/2] ) {
		swap(node,node/2);
		node /= 2;
	}
}

template <class K,class E>
void PriorityQ_heap<K,E>::fixDown(int node) {
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
int PriorityQ_heap<K,E>::greater(int a, int b)  const{
	if (tree[a]>tree[b])
		return a;
	else 
		return b;
}

template <class K,class E>
int PriorityQ_heap<K,E>::lower(int a, int b)  const{
	if (tree[a]<tree[b])
		return a;
	else 
		return b;
}

template <class K,class E>
void PriorityQ_heap<K,E>::swap(int a, int b) {
	priorElement<K,E> tmp;
	tmp = tree[a];
	tree[a] = tree[b];
	tree[b] = tmp;
}

template <class K,class E>
PriorityQ_heap<K,E> & PriorityQ_heap<K,E>::operator= (const PriorityQ_heap & p) {
	if(this != &p){
		leaf = p.leaf;
		dim_max = p.dim_max;
		tree = new priorElement<K,E>[dim_max]; 
		for(int i = 0; i <= p.leaf; i++) {
			tree[i] = p.tree[i];
		}
	}
}

template <class K,class E>
PriorityQ_heap<K,E> & PriorityQ_heap<K,E>::operator= (PriorityQ_heap && p) {
	leaf = p.leaf;
	dim_max = p.dim_max;
	tree = new priorElement<K,E>[dim_max]; 
	for(int i = 0; i <= p.leaf; i++) {
		tree[i] = p.tree[i];
	}
}

template <class K,class E>
bool PriorityQ_heap<K,E>::operator== (const PriorityQ_heap & p) const { 
	if(leaf != p.leaf)
		return false;
	for(int i = 1; i < leaf ;i*=2) {
		if(!equal_level(i,p));
			return false;
	}
	return true;
}

template <class K,class E>
bool PriorityQ_heap<K,E>::equal (const PriorityQ_heap & p) const {   // Two priority queues with binary true are equal if every level of the tree has the same values
	if(leaf != p.leaf)
		return false;
	for(int i = 1; i < leaf ;i*=2) {
		if(!equal_level(i,p))
			return false;
	}
	return true;
}

template <class K,class E>
bool PriorityQ_heap<K,E>::equal_level (int level, const PriorityQ_heap & p) const { 
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
void PriorityQ_heap<K,E>::resize () { 
	priorElement<K,E> * tmp = new priorElement<K,E>[dim_max*2];
	dim_max *= 2;
	for(int i = 1; i<=leaf ; i++) {
		tmp[i] = tree[i];
	}
	tree = tmp;
}

#endif
