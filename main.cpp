#include <iostream>
#include <stdlib.h>  
#include <time.h>     
#include "Stack_linked.h"
#include "Linked_list.h"
#include "Queue_linked.h"
#include "Queue_vector.h"
#include <string>
#include "Set_list.h"
#include "hash_table.h"
#include "Bintree_linked.h"
#include "Bintree_vector.h"
#include "PriorityQ_heap.h"
#include "Tree_vector.h"
#include "Algorithm.h"
#include "Graph_list.h"
#include "Tree_linked.h"
#include "BST.h"
#include "MFSET.h"
#include "Algorithm.h"
using std::cout;
using std::endl;

void tryTree() {
	Tree_linked<int> t;
	Tree_linked<int> t2;
	auto r = t.insert_root(1);
	auto n2 = t.insert_child(2,r);
	t.insert_child(3,r);
	t.insert_child(4,r);
	t.insert_child(5,n2);
	t.insert_child(6,n2);
	t.postOrder(cout);
	t2 = t;
	t2.postOrder(cout);
	t2.insert_child(3,t2.root());
	cout<<t;
	t.insert_last_sub_tree(t.root(),t2);
	cout<<t;
}

void tryPriorQ() {
		PriorityQ_heap<int,char> q;
	srand(time(NULL));
	for(int i = 0; i<100; i++) {
		q.insert(priorElement<int,char>(rand(),rand()%25+65));
	}
	priorElement<int,char> tmp = q.min();
	int i = 0;
	while(!q.empty()) {
		if(tmp>q.min()) {
			break;
		}
		tmp = q.min();
		cout<<tmp<<" "<<i<<endl;
		q.erase();
		i++;
	}
}

void tryMFSET() {
	Set_list<int> s;
	s.add(1);
	s.add(2);
	s.add(3);
	s.add(4);
	s.add(5);
	s.add(6);
	
	MFSET<int> m(s);
	cout<<m<<endl;
	m.merge(1,2);
	cout<<m<<endl;
	m.merge(4,6);
	cout<<m<<endl;
	m.merge(2,5);
	cout<<m<<endl;
	m.merge(5,3);
	cout<<m<<endl;
	Set_list<int> sc;
}

void trySet() {
	srand(time(NULL));
	Set_list<int> s;
	/*s.add(1);
	s.add(2);
	s.add(3);
	s.add(4);
	s.add(5);
	s.add(6);*/
	
	Set_list<int> s2;
	/*s2.add(1);	
	s2.add(3);
	s2.add(6);
	s2.add(7);*/
	
	for(int i = 0 ; i<1000 ; i++) {
		s.add(rand());
		s2.add(rand());
	}
	s-s2;
	cout<<s;
}

void tryGraph() {
	Graph_list<char,short> G(10);
	typename Graph_list<int,short>::Node a1;
	typename Graph_list<int,short>::Node b3;
	typename Graph_list<int,short>::Node c2;
	typename Graph_list<int,short>::Node d4;
	typename Graph_list<int,short>::Node e5;
	typename Graph_list<int,short>::Node f6;
	G.insNode(a1,0);
	G.insNode(b3,1);
	G.insNode(c2,2);
	G.insNode(d4,3);
	G.insNode(e5,4);
	G.insNode(f6,5);
	G.insArc(a1,b3,2);
	G.insArc(a1,c2,1);
	G.insArc(b3,d4,3);
	G.insArc(b3,c2,3);
	G.insArc(c2,e5,1);
	G.insArc(e5,d4,2);
	G.insArc(e5,f6,5);
	G.insArc(d4,f6,2);
	Linked_list<int> list = G.shortestPath(a1,f6);
	cout<<list; 

}

void tryBST() {
	BST<int,char> q;
	srand(time(NULL));
	int v[50];
	int numb = 50;
	int to_erase = 20;
	int temp;
	int erased;
	cout<<"INSERT"<<endl;
	for(int i = 0; i<numb; i++) {
		temp = rand()%50;
		cout<<temp<<endl;
		q.insert(temp,rand()%25+65);
		v[i] = temp;
	}
	cout<<"ERASE"<<endl;
	for(int i = 0; i<to_erase; i++) {
		erased = (v[rand()%numb]);
		cout<<erased<<endl;
		q.erase(erased);
	}
	/*
	cout<<q;
	q.insert(49,'a');
	cout<<q;
	q.insert(3,'b');
	cout<<q;
	q.insert(31,'c');
	cout<<q;
	q.insert(37,'d');
	cout<<q;
	q.insert(29,'e');
	cout<<q;
	q.insert(46,'f');
	cout<<q;	
	q.insert(13,'g');
	cout<<q;
	q.insert(28,'h');
	cout<<q;
	q.insert(2,'i');
	cout<<q;	
	q.insert(28,'l');
	cout<<q;	

	q.erase(3);
	cout<<q;
	q.erase(46);
	cout<<q;
	q.erase(49);
	cout<<q;
	q.erase(28);//problem
	cout<<q;*/
	
	cout<<"SHOW"<<'\n';
	
	int i = 0;
	int tmp = q.min();
	while(!q.empty()) {
		cout<<q;
		if(tmp>q.min()) {
			break;
		}
		tmp = q.min();
		cout<<tmp<<" "<<i<<'\n';
		q.erase(tmp);
		i++;
	}
}

void tryHash() {
	hash_table<int,char> h;
	h[2] = 'a';
	h[3] = 'c';
	h[4] = 'd';
	h[5] = 'e';
	h[2] = 'b';
	cout<<h<<endl;
	h.erase(3);
	hash_table<int,char> h2(h);
	cout<<h2;
}

void tryStack() {
	Stack_linked<int> s;
	int num = 50;
	for(int i = 0; i < num ; i++) {
		s.push(rand());
	}
	Stack_linked<int> s2(s);
	cout<<s2;
	while(!s2.empty()) {
		s2.pop();
	}
}

void tryBintree() {
	Bintree_linked<char> bin;
	typedef typename Bintree_linked<char>::node node;
	node r = bin.insert_root('r');
	node a = bin.insert_lchild('a',r);
	node b = bin.insert_rchild('b',r);
	node c = bin.insert_lchild('c',a);
	node d = bin.insert_rchild('d',a);
	node e = bin.insert_lchild('e',b);
	node f = bin.insert_rchild('f',b);
	cout<<bin<<endl;
	Bintree_linked<char> bin2 = bin;
	bin.delete_sub(r);
	cout<<bin<<endl;
	cout<<bin2<<endl;
	bin2.sub_tree(bin2.rchild(bin2.root()),bin);
	cout<<bin<<endl;
	bin2.delete_sub(bin2.rchild(bin2.root()));
	cout<<bin2<<endl;
	cout<<bin<<endl;
	bin.insert_rsub(bin.root(),bin2);
	cout<<bin;
}


int main(){
	tryTree();
	return 0;
}
