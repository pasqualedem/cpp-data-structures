#ifndef GRAPH_LIST_H
#define GRAPH_LIST_H

#include "Graph.h"
#include "Linked_list.h"
#include "Stack_Linked.h"
#include "Queue_linked.h"
#include "Tree_linked.h"
#include "Set_list.h"
#include "hash_table.h"
#include <limits.h>

class NodeG {
	
	friend std::ostream& operator<<(std::ostream& out, const NodeG & n) {
		out<<"["<<n.id<<"]";
		return out;
	}
	
	private:
		int id;
	public:
		NodeG () {}
		NodeG (int i) {
			id = i;
		}
		
		void setId (int i ) {
			id = i;
		}
		int getId () {
			return id;
		}
	bool operator!= (const NodeG & n) const {
		return id!=n.id;
	}
	bool operator== (const NodeG & n) const {
		return id==n.id;
	}
	bool operator<= (const NodeG & n) const {
		return id<=n.id;
	}
	bool operator< (const NodeG & n) const {
		return id<n.id;
	}
};

template <class W>
class InfoArc {
	public:
		NodeG next;
		W weight;
		
	/*	bool operator==( const InfoArc & I) {
			return (next == I.next && weight == I.weight);
		}*/
};

template <class L,class W>
class InfoNode {
	public:
		L label;
		Linked_list<InfoArc<W> > adjacents;
		bool empty;
		InfoNode() {
			empty = true;
		}
		
	
	/*	bool operator==( const InfoNode & I) {
			if(empty == I.empty && empty)
				return true; //supposing that 2 InfoNodes are equal if both are empty 
			if(label == I.label) {
				if(empty == I.empty) {
					if(adjacents == I.adjacents)
						return true;
				}
			}
			return false;
		}*/
};

template <class L , class W>
class Graph_list : public Graph <L,W, NodeG> {
	public:
		typedef NodeG Node;
		typedef typename Graph<L,W, NodeG>::NodeList NodeList;
		typedef typename Graph<L,W, NodeG>::ArcList ArcList;
		typedef typename Graph<L,W, NodeG>::Label Label;
		typedef typename Graph<L,W, NodeG>::Weight Weight;
		typedef typename Graph<L,W, NodeG>::Arc Arc; 
		Graph_list();
		Graph_list(int);
		Graph_list(const Graph_list &);
		~Graph_list();
		
		bool empty() const ;
		void insNode(Node&) ;
		void insNode(Node&, L) ;
		void insArc(Node, Node, Weight) ;
		void eraseNode(Node) ;
		void eraseArc(Node, Node) ;
		bool node_exists(Node) const;
		bool arc_exists(Node,Node) const;
		NodeList adjacents(Node) const ;
		NodeList nodeList() const ;
		ArcList arcList() const ;
		Label readLabel(Node) const ;
		Label & ref_readLabel(Node) const;
		void writeLabel(Node, Label) ;
		Weight readWeight(Node, Node) const ;
		Weight & ref_readWeight(Node, Node) const;
		void writeWeight(Node, Node, Weight) ;
		
		int numNodes() const{ return num_nodes;} 
		int numArcs() const{ return num_arcs;}
		bool isolated(Node) const;
		void DPS(Node) const;
		void BFS(Node) const;
		bool findPath(Node n, Node n2) const;
		bool isAdjacent (Node n, Node n2) const;
		Tree_linked<int> coverTree(Node) const;
		Linked_list<int> shortestPath(Node,Node) const;
		W totalWeight() const;
		
		Graph_list<L,W>& operator=(const Graph_list<L,W>&); // the assignment operator
		Graph_list<L,W>& operator=( Graph_list<L,W>&&); 
		bool operator==( Graph_list<L,W> & g);
	private:
		InfoNode<L,W> * nodes;
		int num_nodes;
		int num_arcs;
		int dim;
		static const int default_dim = 10;
		void resize();
};

template <class L,class W>
Graph_list<L,W>::Graph_list() {
	dim = default_dim;
	num_nodes = 0;
	num_arcs = 0;
	nodes = new InfoNode<L,W>[dim];
}

template <class L,class W>
Graph_list<L,W>::Graph_list(int dimension) {
	dim = dimension;
	num_nodes = 0;
	num_arcs = 0;
	nodes = new InfoNode<L,W>[dimension];
}

template <class L,class W>
Graph_list<L,W>::Graph_list(const Graph_list<L,W> & g) {
	num_nodes = g.num_nodes;
	num_arcs = g.num_arcs;
	dim = g.dim;
	nodes = new InfoNode<L,W>[dim];
	for(int i = 0; i<dim; i++) 
		nodes[i] = g.nodes[i];
}

template <class L,class W>
Graph_list<L,W>::~Graph_list() {
	delete[] nodes;
}


template <class L,class W>
bool Graph_list<L,W>::empty() const{
	return num_nodes == 0;
}

template <class L,class W>
void Graph_list<L,W>::insNode(Node & n) {
	int i = -1;
	if(num_nodes < dim) {
		i = 0;
		while(!nodes[i].empty)
			i++;
		nodes[i].empty = false;
		num_nodes++;
		n.setId(i);
	}
	else {
		resize();
		insNode(n);
	}
}

template <class L,class W>
void Graph_list<L,W>::insNode(Node & n, L label) {
	int i = -1;
	if(num_nodes < dim) {
		i = 0;
		while(!nodes[i].empty)
			i++;
		nodes[i].empty = false;
		nodes[i].label = label;
		num_nodes++;
		n.setId(i);
	}
	else {
		resize();
		insNode(n,label);
	}
}

template <class L,class W>
void Graph_list<L,W>::insArc(Node n1, Node n2, Weight weight ) {
	bool found = false;
	InfoArc<W> arc;
	arc.weight = weight;
	arc.next = n2;
	nodes[n1.getId()].adjacents.push_back(arc);
	num_arcs++;
}

template <class L,class W>
void Graph_list<L,W>::eraseNode(Node n) {
	if(n.getId()<dim && isolated(n)) {
		nodes[n.getId()].empty = true;
		num_nodes--;
	} 
}

template <class L,class W>
void Graph_list<L,W>::eraseArc(Node n1, Node n2) {
	if(n1.getId()<dim && n2.getId()<dim ) {
		auto arc = nodes[n1.getId()].adjacents.begin();
		while(!nodes[n1.getId()].adjacents.end(arc) && nodes[n1.getId()].adjacents.read(arc).next != n2) 
			arc = nodes[n1.getId()].adjacents.next(arc);
		if (!nodes[n1.getId()].adjacents.end(arc) ) {
			nodes[n1.getId()].adjacents.erase(arc);
			num_arcs--;
		}
	}
}

template <class L,class W>
bool Graph_list<L,W>::node_exists(Node n) const {
	if(n.getId()<dim)
		return !nodes[n.getId()].empty;
	else
		return false;
}

template <class L,class W>
bool Graph_list<L,W>::arc_exists(Node n1, Node n2) const{
	if(n1.getId()<dim && n2.getId()<dim )  {
		auto arc = nodes[n1.getId()].adjacents.begin();
		while(!nodes[n1.getId()].adjacents.end(arc) && nodes[n1.getId()].adjacents.read(arc).next != n2) 
			arc = nodes[n1.getId()].adjacents.next(arc);
		if (!nodes[n1.getId()].adjacents.end(arc) )
			return true;
		}
	return false;
}

template <class L,class W>
typename Graph_list<L,W>::NodeList Graph_list<L,W>::adjacents (Node n) const{ 
	NodeList l;
	auto arc = nodes[n.getId()].adjacents.begin();
	while(!nodes[n.getId()].adjacents.end(arc)) {
		l.push_back(new NodeG(nodes[n.getId()].adjacents.read(arc).next.getId() ));
		arc = nodes[n.getId()].adjacents.next(arc);
	}
	return l;
}

template <class L,class W>
typename Graph_list<L,W>::NodeList Graph_list<L,W>::nodeList () const{ 
	NodeList l;
	for(int i = 0 ; i< dim ;i++) {
		if(!nodes[i].empty)
			l.push_back(new NodeG(i));
	}
	return l;
}

template <class L,class W>
typename Graph_list<L,W>::ArcList Graph_list<L,W>::arcList () const{ 
	ArcList l;
	for(int i = 0 ; i< dim ;i++) {
		if(!nodes[i].empty) {
			auto arc = nodes[i].adjacents.begin();
			NodeG tmp(i);
			while(!nodes[i].adjacents.end(arc)) {
				l.push_back(new Arc(tmp,nodes[i].adjacents.read(arc).next,nodes[i].adjacents.read(arc).weight));
				arc = nodes[i].adjacents.next(arc);
			}
		}
	}
	return l;
}

template <class L,class W>
typename Graph_list<L,W>::Label Graph_list<L,W>::readLabel(Node n) const{ 
	if(n.getId() < dim) 
		if(!nodes[n.getId()].empty)
			return nodes[n.getId()].label;
}

template <class L,class W>
typename Graph_list<L,W>::Label & Graph_list<L,W>::ref_readLabel(Node n) const{ 
	if(n.getId() < dim) 
		if(!nodes[n.getId()].empty)
			return nodes[n.getId()].label;
}

template <class L,class W>
void Graph_list<L,W>::writeLabel(Node n, Label label) { 
	if(n.getId() < dim) 
		if(!nodes[n.getId()].empty)
			nodes[n.getId()].label = label;
}

template <class L,class W>
typename Graph_list<L,W>::Weight Graph_list<L,W>::readWeight(Node n1, Node n2) const{ 
	if(n1.getId() < dim) 
		if(!nodes[n1.getId()].empty) {
			auto arc = nodes[n1.getId()].adjacents.begin();
			while(!nodes[n1.getId()].adjacents.end(arc) && nodes[n1.getId()].adjacents.read(arc).next != n2 )
				arc = nodes[n1.getId()].adjacents.next(arc);
			if(!nodes[n1.getId()].adjacents.end(arc)) {
				return nodes[n1.getId()].adjacents.read(arc).weight;
			}
		}
}

template <class L,class W>
typename Graph_list<L,W>::Weight & Graph_list<L,W>::ref_readWeight(Node n1, Node n2) const{ 
	if(n1.getId() < dim) 
		if(!nodes[n1.getId()].empty) {
			auto arc = nodes[n1.getId()].adjacents.begin();
			while(!nodes[n1.getId()].adjacents.end(arc) && nodes[n1.getId()].adjacents.read(arc).next != n2 )
				arc = nodes[n1.getId()].adjacents.next(arc);
			if(!nodes[n1.getId()].adjacents.end(arc)) {
				return nodes[n1.getId()].adjacents.read(arc).weight;
			}
		}
}

template <class L,class W>
void Graph_list<L,W>::writeWeight(Node n1, Node n2, Weight weight) { 
	if(n1.getId() < dim) 
		if(!nodes[n1.getId()].empty) {
			auto arc = nodes[n1.getId()].adjacents.begin();
			while(!nodes[n1.getId()].adjacents.end(arc) && nodes[n1.getId()].adjacents.read(arc).next != n2 )
				arc = nodes[n1.getId()].adjacents.next(arc);
			if(!nodes[n1.getId()].adjacents.end(arc)) {
				nodes[n1.getId()].adjacents.ref_read(arc).weight = weight;
			}
		}
}


template <class L,class W>
bool Graph_list<L,W>::isolated (Node n) const {
	if(n.getId()<dim) {
		bool found = true;
		if(nodes[n.getId()].adjacents.empty()) {
			found = false;
			int i = 0;
			while(!found && i<dim) {
				if(!nodes[i].empty) {
					auto arc = nodes[i].adjacents.begin();
					while(!nodes[i].adjacents.end(arc) && nodes[i].adjacents.read(arc).next != n )
						arc = nodes[i].adjacents.next(arc);
					if(!nodes[i].adjacents.end(arc))
						found = true;		
				}
				i++;
			}
		}
		return !found;
	}
}

template<class L, class W>
void Graph_list<L,W>::DPS(Node n) const{
	if(!empty() && n.getId()<dim && !nodes[n.getId()].empty) {
		bool * mark = new bool[num_nodes];
		bool * stacked = new bool[num_nodes];
		for(int i = 0;i<num_nodes; i++) {
			mark[i] = false;
			stacked[i] = false;
		}
		Stack_linked<Node> s;
		std::cout<<"(";
		s.push(n);
		Node tmp;
		while(!s.empty()) {
			tmp = s.ref_top();
			std::cout<<readLabel(tmp);
			s.pop();
			mark[tmp.getId()] = true;
			auto pos = nodes[tmp.getId()].adjacents.begin();
			while(! nodes[tmp.getId()].adjacents.end(pos)) {
				if(!stacked[nodes[tmp.getId()].adjacents.read(pos).next.getId()] && !mark[nodes[tmp.getId()].adjacents.read(pos).next.getId()]) 
					s.push(nodes[tmp.getId()].adjacents.ref_read(pos).next);
				pos = nodes[tmp.getId()].adjacents.next(pos);
			}
			if(!s.empty())
				std::cout<<", ";
		}
		cout<<" )";
	}
}

template<class L, class W>
void Graph_list<L,W>::BFS(Node n) const{
	if(!empty() && n.getId()<dim && !nodes[n.getId()].empty) {
		bool * mark = new bool[num_nodes];
		bool * queued = new bool[num_nodes];
		for(int i = 0;i<num_nodes; i++) {
			mark[i] = false;
			queued[i] = false;
		}
		Queue_linked<Node> q;
		std::cout<<"(";
		q.enqueue(n);
		Node tmp;
		while(!q.empty()) {
			tmp = q.ref_front();
			std::cout<<readLabel(tmp);
			q.dequeue();
			mark[tmp.getId()] = true;
			auto pos = nodes[tmp.getId()].adjacents.begin();
			while(! nodes[tmp.getId()].adjacents.end(pos)) {
				if(!queued[nodes[tmp.getId()].adjacents.read(pos).next.getId()] && !mark[nodes[tmp.getId()].adjacents.read(pos).next.getId()]) 
					q.enqueue(nodes[tmp.getId()].adjacents.ref_read(pos).next);
				pos = nodes[tmp.getId()].adjacents.next(pos);
			}
			if(!q.empty())
				std::cout<<", ";
		}
		cout<<" )";
	}
}

template<class L, class W>
bool Graph_list<L,W>::findPath(Node n, Node n2) const{
	if(!empty() && n.getId()<dim && !nodes[n.getId()].empty) {
		bool * mark = new bool[num_nodes];
		bool * stacked = new bool[num_nodes];
		for(int i = 0;i<num_nodes; i++) {
			mark[i] = false;
			stacked[i] = false;
		}
		Stack_linked<Node> s;
		Tree_linked<Node> rooted;
		s.push(n);
		rooted.insert_root(n);
		Node tmp;
		auto parent = rooted.root();
		auto child = rooted.root();
		bool found = false;
		tmp = s.ref_top();
		mark[tmp.getId()] = true;
		auto pos = nodes[tmp.getId()].adjacents.begin();
			if ( tmp.getId()  == n2.getId()) 
				found = true;
			while(! nodes[tmp.getId()].adjacents.end(pos) && !found) {
				if(!stacked[nodes[tmp.getId()].adjacents.read(pos).next.getId()] && !mark[nodes[tmp.getId()].adjacents.read(pos).next.getId()]) {
					s.push(nodes[tmp.getId()].adjacents.ref_read(pos).next);
				}
				pos = nodes[tmp.getId()].adjacents.next(pos);
			}
		while(!s.empty() && !found) {
			tmp = s.ref_top();
			s.pop();
			while(!isAdjacent(rooted.read(parent),tmp))
				parent = rooted.parent(parent);
			child = rooted.insert_child(tmp,parent);
			parent = child;
			mark[tmp.getId()] = true;
			pos = nodes[tmp.getId()].adjacents.begin();
			if ( tmp.getId()  == n2.getId()) 
				found = true;
			while(! nodes[tmp.getId()].adjacents.end(pos) && !found) {
				if(!stacked[nodes[tmp.getId()].adjacents.read(pos).next.getId()] && !mark[nodes[tmp.getId()].adjacents.read(pos).next.getId()]) 
					s.push(nodes[tmp.getId()].adjacents.ref_read(pos).next);
				pos = nodes[tmp.getId()].adjacents.next(pos);
			}
		}
		if(found) {
			std::cout<<"( ";
			while(child != rooted.root()) {
				std::cout<<readLabel(rooted.read(child));
				std::cout<<", ";
				child = rooted.parent(child);
			}
			std::cout<<readLabel(rooted.read(rooted.root()));
			std::cout<<" )";
			return true;
		}
	}
	return false;
}

template<class L, class W>
bool Graph_list<L,W>::isAdjacent(Node n, Node n2) const{
	auto pos = nodes[n.getId()].adjacents.begin();
	while( !nodes[n.getId()].adjacents.end(pos) && nodes[n.getId()].adjacents.read(pos).next.getId() != n2.getId() )
		pos = nodes[n.getId()].adjacents.next(pos);
	if(nodes[n.getId()].adjacents.end(pos))
		return false;
	else
		return true;
}

template<class L, class W>
Tree_linked<int> Graph_list<L,W>::coverTree(Node n) const{
	Set_list<Node> s;
	hash_table<L,L> DIST(num_nodes*2);
	hash_table<int,int> T(num_nodes*2);
	W w_max = totalWeight();
	for(int i = 0; i< num_nodes ; i++) {
		DIST[i] = w_max;
		T[i] = n.getId();
	}
	DIST[n.getId()] = 0;
	s.add(n);
	Node tmp;
	while(!s.empty()) {
		tmp = s.read();
		s.erase(tmp);
		auto pos = nodes[tmp.getId()].adjacents.begin();
		Node j;
		while(!nodes[tmp.getId()].adjacents.end(pos)) {
			j = nodes[tmp.getId()].adjacents.read(pos).next;
			if(DIST[tmp.getId()] + nodes[tmp.getId()].adjacents.read(pos).weight <= DIST[j.getId()] ) {
				DIST[j.getId()] = DIST[tmp.getId()] + nodes[tmp.getId()].adjacents.read(pos).weight;
				T[j.getId()] = tmp.getId();
			}
			s.add(j);
			pos = nodes[tmp.getId()].adjacents.next(pos);
		}
	}
	T.erase(0);
	return Tree_linked<int> (n.getId(),T);
}

template<class L, class W>
Linked_list<int> Graph_list<L,W>::shortestPath(Node n,Node n2) const{
	Tree_linked<int> t= coverTree(n);
	Linked_list<int> l;
	typename Tree_linked<int>::node w = t.find(n2.getId());
	if(!t.is_null(w)) {
		while(w!= t.root()) {
			l.push_front(t.read(w));
			w = t.parent(w);
		}
		l.push_front(t.read(w));
	}
	return l;
}

template <class L,class W>  // returns the total weight of the arcs, (used in shortesPath to initialize DIST instead of INT_MAX) 
W Graph_list<L,W>::totalWeight () const{ 
	W tot;
	for(int i = 0 ; i< dim ;i++) {
		if(!nodes[i].empty) {
			auto arc = nodes[i].adjacents.begin();
			NodeG tmp(i);
			while(!nodes[i].adjacents.end(arc)) {
				tot += nodes[i].adjacents.read(arc).weight;
				arc = nodes[i].adjacents.next(arc);
			}
		}
	}
	return tot;
}

template<class L, class W>
Graph_list<L,W>& Graph_list<L,W>::operator=(const Graph_list<L,W> & g) {
	num_nodes = g.num_nodes;
	num_arcs = g.num_arcs;
	dim = g.dim;
	nodes = new InfoNode<L,W>[dim];
	for(int i = 0; i<dim; i++) 
		nodes[i] = g.nodes[i];
	return *this;
}

template<class L, class W>
Graph_list<L,W>& Graph_list<L,W>::operator=( Graph_list<L,W> && g) {
	if(this != &g) {
		num_nodes = g.num_nodes;
		num_arcs = g.num_arcs;
		dim = g.dim;
		nodes = new InfoNode<L,W>[dim];
		for(int i = 0; i<dim; i++) 
			nodes[i] = g.nodes[i];
	}
	return *this;
}

template<class L, class W>
void Graph_list<L,W>::resize() {
	dim*=2;
	InfoNode<L,W> * tmp = new InfoNode<L,W>[dim];
	for(int i = 0; i<dim/2; i++) 
		tmp[i] = nodes[i];
	nodes = tmp;
}
/*
template<class L, class W>
bool Graph_list<L,W>::operator==( Graph_list<L,W> & g) {
	if(num_nodes == g.num_nodes)
		if(num_arcs == g.num_arcs) {
			bool found = false;
			int k = 0;
			int j;
			for(int i = 0; i < dim && k<num_nodes ; i++) {
				found = false;
				if(!nodes[i].empty) {
					j=0;
					while(j<g.dim && !found) {
						if(nodes[i] == g.nodes[j])
							found = true;
						j++;
					}
					if(!found)
						return false;
					k++;	
				}
			}
			return true;	
		}
	return false;
}*/

#endif
