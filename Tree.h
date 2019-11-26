#ifndef _TREE_
#define _TREE_

#include <iostream>
#include <algorithm>
#include "hash_table.h"

template <class T,class N>
class Tree {
	public:
		typedef T value_type;
		typedef N node;
		
		virtual void create() = 0;
		virtual bool empty() const = 0;
		virtual node root() const = 0;
		virtual node parent(node) const = 0;
		virtual bool leaf(node) const = 0;
		virtual node fchild(node) const = 0;
		virtual bool lsibling(node) const = 0;
		virtual node nsibling(node) const = 0;
		virtual void delete_sub(node) = 0;
		virtual value_type read(node) const = 0;
		virtual void write(const value_type&, node) = 0;
		virtual node insert_root () = 0;
		virtual node insert_child(node) = 0;
		/*virtual void insert_first_sub_tree(node,const Tree&) = 0; // insert a subtree where the sub tree is the first child of node
		virtual void insert_sub_tree(const node,Tree&) = 0; // insert a subtree where the sub tree is the next sibling of node*/
		
		virtual void print(std::ostream&) const;
		virtual bool is_null(node) const = 0;	// che if a node is null_node
		virtual node null_node() const = 0; // returns the null node	
		int height() const;
		int sub_height(node) const;
		int width() const;
		int depth(node) const;
		bool isMember(const value_type &) const;
		node find(const value_type &) const;
		void BFS(std::ostream&) const;
		void inOrder(std::ostream&) const;
		void postOrder(std::ostream&) const;
		void toSet(Set<T> & s) const;

	private:
    	virtual void printSubTree(const node,std::ostream&) const;
};


template <class T, class N>
void Tree<T,N>::print(std::ostream& out) const{
	if (!empty())
		printSubTree(root(),out);
	else 
		out << "{}" << std::endl;
	out << std::endl;
}

template <class T, class N>
void Tree<T,N>::printSubTree(const node n,std::ostream& out) const{
	out << "{" << read(n)<<" ";
	if(!leaf(n)) {
		node tmp = fchild(n);
		printSubTree(tmp,out);
		tmp = nsibling(tmp); 
		while(!is_null(tmp)) {
			out << ", ";
			printSubTree(tmp,out); 
			tmp = nsibling(tmp);
		}
	}
	out << " }";
}

template<class T, class N>
std::ostream& operator<<(std::ostream& out, const Tree<T, N> & t) {
    t.print(out);
    return out;
}


template <class T, class N>
int Tree<T,N>::height () const {
	if(empty())
		return 0;
	else
		return sub_height(root());
} 

template <class T, class N>
int Tree<T,N>::depth(node u) const {
	int d = 1;
	while(u!= root()) {
		d++;
		u = parent(u);
	}
	return d;
}

template <class T, class N>
int Tree<T,N>::sub_height (node u) const {
	if(leaf(u))
		return 1;
	int max = 0;
	int height;
	node tmp = fchild(u);
	while(!lsibling(tmp)) {
		height = sub_height(tmp); 
		if(max < height)
			max = height;
		tmp = nsibling(tmp); 
	}
	height = sub_height(tmp); 
	if(max < height)
		max = height;
	return max+1;
} 

template<class T, class N>
class Node_level {
	public:
		typename Tree<T,N>::node n;
		unsigned int level;
		
		Node_level (typename Tree<T,N>::node n1, int l ) {
			n = n1;
			level = l;
		}
		Node_level () {
		}
}; 

template <class T, class N>
int Tree<T,N>::width() const{
	int max_width = 0;
	if(!empty()) {
		int n_levels = height(); 
		int * levels = new int[n_levels];
		for(int i = 0; i< n_levels; i++) 
			levels[i] = 0;
		Queue_linked<Node_level<T,N> > q;
		q.enqueue( Node_level<T,N>(root(),0) );
		int cur_level;
		levels[0] = 1;
		node tmp;
		Node_level<T,N> element;
		node child;
		while(!q.empty()) {
			element = q.front();
			tmp = element.n;
			cur_level = element.level + 1;
			if(!leaf(tmp)) {
				child = fchild(tmp);
				while(!lsibling(child)) {
					levels[cur_level]++;
					q.enqueue(Node_level<T,N>(child,cur_level));
					child = nsibling(child);
				}
				levels[cur_level]++;
				q.enqueue(Node_level<T,N>(child,cur_level));
			}
			q.dequeue();
		}
		max_width = *(std::max_element(levels,levels+n_levels));
	}
	return max_width;
}


template<class T, class N> 
bool Tree<T,N>::isMember(const value_type & v) const{ 
	if(!empty()) {
		Queue_linked<node> q;
		node tmp;
		node this_child;
		q.enqueue(root());
		while(!q.empty()) {
			tmp = q.front();
			if(read(tmp) == v)
				return true;
			if(!leaf(tmp)) {
				this_child = fchild(tmp);
				q.enqueue(this_child);
				this_child = nsibling(this_child);
				while(!is_null(this_child))  {// After is reached the last sibling, nsibling returns null node
					q.enqueue(this_child);
					this_child = nsibling (this_child);
				}
				
			}
			q.dequeue();		 
		}
	}
	return false;
}

template<class T, class N> 
typename Tree<T,N>::node Tree<T,N>::find(const value_type & v) const{ 
	if(!empty()) {
		Queue_linked<node> q;
		node tmp;
		node this_child;
		q.enqueue(root());
		while(!q.empty()) {
			tmp = q.front();
			if(read(tmp) == v)
				return tmp;
			if(!leaf(tmp)) {
				this_child = fchild(tmp);
				q.enqueue(this_child);
				this_child = nsibling(this_child);
				while(!is_null(this_child))  {// After is reached the last sibling, nsibling returns null node
					q.enqueue(this_child);
					this_child = nsibling (this_child);
				}
				
			}
			q.dequeue();		 
		}
	}
	return null_node();
}

template<class T, class N> 
void Tree<T,N>::BFS(std::ostream & out) const{ 
	out<<"[";
	if(!empty()) {
		Queue_linked<node> q;
		node tmp;
		node this_child;
		q.enqueue(root());
		while(!q.empty()) {
			tmp = q.front();
			out<<read(tmp);
			if(!leaf(tmp)) {
				this_child = fchild(tmp);
				q.enqueue(this_child);
				this_child = nsibling(this_child);
				while(!is_null(this_child))  {// After is reached the last sibling, nsibling returns null node
					q.enqueue(this_child);
					this_child = nsibling (this_child);
				}
				
			}
			q.dequeue();
			if(!q.empty())
				out<<", ";		 
		}
	}
	out<<"]";
}

template<class T, class N> 
void Tree<T,N>::inOrder(std::ostream & out) const{ 
	out<<"[";
	if(!empty()) {
		Stack_linked<node> s;
		node tmp;
		node this_child;
		s.push(root());
		while(!s.empty()) {
			tmp = s.top();
			s.pop();
			out<<read(tmp);
			if(!leaf(tmp)) {
				this_child = fchild(tmp);
				s.push(this_child);
				this_child = nsibling(this_child);
				while(!is_null(this_child))  {// After is reached the last sibling, nsibling returns null node
					s.push(this_child);
					this_child = nsibling (this_child);
				}
			}
			if(!s.empty())
				out<<", ";		 
		}
	}
	out<<"]";
}

template<class T, class N> 
void Tree<T,N>::postOrder(std::ostream & out) const{ 
	Stack_linked<T> app;
	if(!empty()) {
		Stack_linked<node> s;
		node tmp;
		node this_child;
		s.push(root());
		while(!s.empty()) {
			tmp = s.top();
			app.push(read(tmp));
			s.pop();
			if(!leaf(tmp)) {
				this_child = fchild(tmp);
				s.push(this_child);
				this_child = nsibling(this_child);
				while(!is_null(this_child))  {// After is reached the last sibling, nsibling returns null node
					s.push(this_child);
					this_child = nsibling (this_child);
				}
			}		 
		}
	}
	cout<<app;
}

template<class T, class N> 
void Tree<T,N>::toSet(Set<T> & s) const{ 
	if(!empty()) {
		Queue_linked<node> q;
		node tmp;
		node this_child;
		q.enqueue(root());
		while(!q.empty()) {
			tmp = q.front();
			s.add(read(tmp));
			if(!leaf(tmp)) {
				this_child = fchild(tmp);
				q.enqueue(this_child);
				this_child = nsibling(this_child);
				while(!is_null(this_child))  {// After is reached the last sibling, nsibling returns null node
					q.enqueue(this_child);
					this_child = nsibling (this_child);
				}
				
			}
			q.dequeue();	 
		}
	}
}
#endif
