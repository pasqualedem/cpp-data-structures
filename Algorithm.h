#ifndef _ALGORITHM_
#define _ALGORITHM_

#include "Linked_list.h"
#include "Stack_linked.h"
#include <string>
#include "Queue_linked.h"
#include "hash_table.h"

using std::string;

template <class T>
void swap(int a, int b, T vet[]) {
	T  tmp;
	tmp = vet[a];
	vet[a] = vet[b];
	vet[b] = tmp;
}

template <class T>
int greater(int a, int b, T vet[]) {
	if (vet[a]>vet[b])
		return a;
	else 
		return b;
}

template <class T>
void fixUp (int leaf ,Linked_list<T> & data, T heap[] , typename Linked_list<T>::position pos[]) {
	while(leaf>1 && heap[leaf] > heap[leaf/2] ) {
		swap(leaf,leaf/2, heap);
		data.swap(pos[leaf],pos[leaf/2]);
		leaf /= 2;
	}
}

template <class T>
void fixDown (int leaf, Linked_list<T> & data, T heap[] , typename Linked_list<T>::position pos[]) {
	swap(leaf,1,heap);
	data.swap(pos[leaf],pos[1]);
	//swap(leaf,1,pos);
	leaf--;
	int node = 1;
	int grt;
	if(leaf>=node*2+1)
		grt	= greater(node*2,node*2+1,heap);
	else
		grt = node*2;
	while(grt<leaf+1 && heap[node] < heap[grt]) {
		swap(node,grt,heap);
		data.swap(pos[node],pos[grt]);
		//swap(node,grt,pos);
		node = grt;
		if(leaf>=node*2+1)
			grt	= greater(node*2,node*2+1,heap);
		else
			grt = node*2;
	}
}

template <class T>
void HeapSort (Linked_list<T> & data) {
	int size = data.size();
	T * heap = new T[size+1];
	typename Linked_list<T>::position * pos = new typename Linked_list<T>::position[size+1];
	int leaf = 1;
	for(auto it = data.begin();  !data.end(it) ; it = data.next(it)) {
	 	heap[leaf] = data.read(it);
	 	pos[leaf] = it;
	 	fixUp(leaf,data,heap,pos);
	 	leaf++;
	}
	leaf--;
		while(leaf > 1) {
	 	fixDown(leaf,data,heap,pos);
	 	leaf--;
	}
}

template <class T>
int isOrdered(Linked_list<T> & data) {
	// 0 not ordered , 1  ordered , -1 desc oredered  
	int size = data.size();
	if(size > 1) {
		typename Linked_list<T>::position pos = data.begin();
		if(data.read(pos) <= data.read(data.next(pos))) {
			while(data.read(pos) <= data.read(data.next(pos)) && !data.end(data.next(pos)) )
				pos = data.next(pos);
			if(data.end(data.next(pos)))	
				return 1;
			else 
				return 0;
		}
		if(data.read(pos) >= data.read(data.next(pos))) {
			while(data.read(pos) >= data.read(data.next(pos)) && !data.end(data.next(pos)) )
				pos = data.next(pos);
			if(data.end(data.next(pos)))	
				return 1;
			else 
				return 0;
		}
				
	}
	else
		return 1;
}

template <class T>
void MergeSort(T * v, T  * w,T * z, int n, int m, int p) {
	int i = 0;
	int j = 0;
	int k = 0;
	while( i<n && j < m) {
		if (v[i]<w[j]) {
			z[k] = v[i];
			i++;
		}
		else {
			z[k] = w[j];
			j++;
		}
		k++;
	}
}

template <class T>
void NaturalMergeSort(int begin, int end, T * v) {
	if(end == 1) {
		if(v[begin] > v[end])
			swap(begin,end,v);
	}
	else {
		NaturalMergeSort(begin,end/2, v);
		NaturalMergeSort(end - (end/2) + 1, end, v);
		T * z = new T[end+1];
		MergeSort(v, v+(end/2), z , (end+1)/2 , end-(end/2), end+1 );
		v = z ;
	}
}


template <class T>
void QuickSort(int lower,int upper, T v[]) {
	Stack_linked<int> s;
	s.push(lower);
	s.push(upper);
	int l,r;
	T pivot;
	while(!s.empty()) {
		upper = r = s.top();
		s.pop();
		lower = l = s.top();
		s.pop();
		pivot = v[(l+r)/2];
		while(l<r) {
			while(v[l]<pivot)
				l++;
			while(v[r]>pivot)
				r--;
			if(l<=r) {
				swap(l,r,v);
				l++;
				r--;
			}	
		}
		if(l<upper) {
			s.push(l);
			s.push(upper);
		}
		if(r>lower) {
			s.push(lower);
			s.push(r);
		}
	}
}

bool OpPrior (char a, char b) {
	hash_table<char,int> h;
	h['('] = 1;
	h['+'] = 2;
	h['-'] = 2;
	h['*'] = 3;
	h['/'] = 3;
	h[')'] = 4;
	return h[a] > h[b];
}

bool isNumber (char a) {
	return  0 <= (a-48) && (a-48) <= 9;
}

string toPost (string infissa) {
	Stack_linked<char> s;
	Queue_linked<char> q;
	int n = infissa.length();
	int i = 0;
	while(i < n) {
		if(infissa[i] == ' ') {
			i++;
			continue;
		}
		if(isNumber(infissa[i]))
			q.enqueue(infissa[i]);
		else if (s.empty())
			s.push(infissa[i]);
		else if (infissa[i] == '(')
			s.push(infissa[i]);
		else if (infissa[i] == ')') {
			while (s.top() != '(') {
				q.enqueue(s.top());
				s.pop();
			}
			s.pop();
		}
		else {
			while ( OpPrior(s.top(),infissa[i]) ) {
				q.enqueue(s.top());
				s.pop();
			}
			s.push(infissa[i]);
		}
	i++;
	}
	while(!s.empty()) {
		q.enqueue(s.top());
		s.pop();
	}
	string post = "";
	char tmp;
	while(!q.empty()) {
		tmp = q.front();
		post+=tmp;
		post+=' ';
		q.dequeue();
	}
	return post;
}












#endif
