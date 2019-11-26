#ifndef GRAPH_H
#define GRAPH_H

#include "Linked_list.h"
#include <iostream>


template<class P, class N>
class Arc_ {
	
	friend std::ostream& operator<<(std::ostream& out, const Arc_<P,N> & a) {
		out<<"("<<a.node1<<","<<a.node2<<","<<a.weight<<")";
		return out;
	}
	
 public:
	N node1;
	N node2;
	P weight;
	
	Arc_(N n1,N n2, P w) {
		node1 = n1;
		node2 = n2;
		weight = w;
	}

};


template<class L, class W, class N>
	class Graph {
public:
	typedef L Label;
	typedef W Weight;
	typedef N Node;
	
	typedef Arc_<Weight, Node> Arc;
	typedef Linked_list<Node*> NodeList;
	typedef Linked_list<Arc*> ArcList;
	typedef typename Linked_list<Node*>::position NodeListPos;
	
	virtual bool empty() const = 0;
	virtual void insNode(Node&) = 0;
	virtual void insArc(Node, Node, Weight) = 0;
	virtual void eraseNode(Node) = 0;
	virtual void eraseArc(Node, Node) = 0;
	virtual bool node_exists(Node) const= 0;
	virtual bool arc_exists(Node,Node) const = 0;
	virtual NodeList adjacents(Node) const = 0;
	virtual NodeList nodeList() const = 0;
	virtual ArcList arcList() const = 0;
	virtual Label readLabel(Node) const = 0;
	virtual void writeLabel(Node, Label) = 0;
	virtual Weight readWeight(Node, Node) const = 0;
	virtual void writeWeight(Node, Node, Weight) = 0;
	
	virtual int numNodes() const = 0;
	virtual int numArcs() const = 0;
	virtual int inDegree(Node) const ;
	virtual int outDegree(Node) const ;
	virtual double meanOutDegree() const ;
	virtual ~Graph(){};
	

};


template<class L, class W, class N>
std::ostream& operator<<(std::ostream& out, const Graph<L,W,N> & g) {
    typename Graph<L,W,N>::NodeList nodes = g.nodeList();
    typename Graph<L,W,N>::ArcList arcs = g.arcList();
    auto pos = nodes.begin();
    out<<"[ ";
    out<<"[";
    do {
    	out<<"("<<g.readLabel(*nodes.ref_read(pos))<<")";
    	pos = nodes.next(pos);
		if(!nodes.end(pos))
			out<<", ";
	} while(!nodes.end(pos));
	out<<"]";
	auto a_pos = arcs.begin();
	out<<" [";
    do {
    	out<<"("<<g.readLabel(arcs.ref_read(a_pos)->node1)<<","<<g.readLabel(arcs.ref_read(a_pos)->node2)<<","<<arcs.ref_read(a_pos)->weight<<")";
    	a_pos = arcs.next(a_pos);
		if(!arcs.end(a_pos))
			out<<", ";
	} while(!arcs.end(a_pos));
	out<<"] ]";
    return out;
}

template<class L, class W, class N>
int Graph<L,W,N>::inDegree(Node n) const {
	ArcList A = arcList();
	int count = 0;
	for(auto arc = A.begin(); !A.end(arc); arc = A.next(arc)) {
		if(A.read(arc)->node2 == n)
			count++;
	}
	return count;
}

template<class L, class W, class N>
int Graph<L,W,N>::outDegree(Node n) const {
	return adjacents(n).size();
}

template<class L, class W, class N>
double Graph<L,W,N>::meanOutDegree() const {
	NodeList nodes = nodeList();
	int avg = 0;
	for(auto nod = nodes.begin(); !nodes.end(nod); nod = nodes.next(nod)) {
		avg += adjacents( *(nodes.read(nod)) ).size();
	}
	avg /= nodes.size();
	return avg;
}

#endif
