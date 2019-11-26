#ifndef HASH_TABLE_H
#define HASH_TABLE_H

#include <string>
#include "dictionary.h"
#include "Hashing.h"
#include <iostream>
#include "Linked_list.h"

using std::string;



/* hash_table class with linear probing */

template<class K, class E>
class mypair;

template <class K, class E>
class hash_table : public dictionary < K , E >{
	public:
  
  	bool empty() const{
    	return (dsize == 0);
  	};	
  
  	int size() const{
    	return dsize;
  	};		
  		hash_table();
		hash_table(int);	    // the constructor
		hash_table(const hash_table<K,E> &);
		void erase(const K& k);	
		void modify(const K& k, const E& e);
		void create(){};
		int search(const K& , bool inserting = false) const;
		mypair< K, E>* find(const K&, bool inserting = false ) const;
		void insert( mypair< K, E>& );
		void insert(const K & k, const E & e);
		void insert(const K & k);
		
		bool containsValue(const E& e) const;
		Linked_list<E> values() const;
		Linked_list<K> keys(const E & e) const;
		Linked_list<K> keys() const;
		void resize();
		
		hash_table<K,E> & operator= (const hash_table<K,E> &);
		hash_table<K,E> & operator= ( hash_table<K,E> &&);
		bool operator == ( const hash_table<K,E> &);
		E & operator[](K i);
		E  operator[] (K i) const;
		K & read_key(int i) const;
		E & read_value(int i) const;
		int next(int i) const;
		bool end(int i) const;
		
		friend  std::ostream & operator<<(std::ostream & os, hash_table<K,E> h) {
			os<<"[ ";
			int i = 0;
			int j = 0;
			while(j<h.dsize){
				if(h.table[i]!=NULL){
					os<<"("<<h.table[i]->first<<",";
					os<<h.table[i]->second<<")";
					if(j!=h.dsize-1)
						os<<" , ";
					j++;
				}
				i++;
			}
			os<<" ]";
			return os;
		}
	private:
		mypair<K, E>** table;    // the hash table
 		hash<K> hashm;		            // maps type K to nonnegative integer
 		int dsize;		                // number of pairs in dictionary
 		int divisor;		            // hash function divisor
 		bool * erased;
 		static int default_divisor;
};


template<class K, class E>
hash_table<K,E>::hash_table(){
	divisor = 100;
	dsize = 0;
	erased = new bool[divisor];
	table = new mypair<K, E>* [divisor];
	for (int i=0; i<divisor; i++) {
    	table[i] = NULL;
    	erased[i] = false;
    }
}

template<class K, class E>
hash_table<K,E>::hash_table(int the_divisor) {
	divisor = the_divisor;
	dsize = 0;
	erased = new bool[divisor];
	table = new mypair<K, E>* [divisor];
	for (int i=0; i<divisor; i++) {
    	table[i] = NULL;
    	erased[i] = false;
    }
}

template<class K, class E>
hash_table<K,E>::hash_table(const hash_table<K,E> & h) {
	divisor = h.divisor;
	table = new mypair<K,E> * [divisor];
	erased = new bool [divisor];
	dsize = h.dsize;
	mypair<K,E> * pair;
	for(int i = 0;i<divisor;i++) {
		if(h.table[i] == NULL)
			table[i] = NULL;
		else {
			pair = new mypair<K,E>;
			pair->first = h.table[i]->first; 
			pair->second = h.table[i]->second; 
			table[i] = pair;
		}
		erased[i] = h.erased[i];
	}
}
/* This method returns a bucket b in the table that satisfies exactly one of the following:
 * 1) table[b] points to a pair whose key is the_key
 * 2) no pair in the table has the key the_key, table[b] is NULL
 * 3) no pair in the table has the the_key, table[b] has a key other than the_key, and the
 *   table is full
 */

template<class K, class E>
int hash_table<K,E>::search(const K& the_key,bool inserting) const
{
  int i = (int) hashm(the_key) % divisor;   // the home bucket
  int j = i;
  do {
    if ((table[j] == 0x0 && (!erased[j]  || inserting )) || table[j]->first == the_key  )
    	return j;
    j = (j+1) % divisor;                    // the next bucket
  } while (j != i);

  return j;                                 // the table is full
}

/* The method hash_table<K,E>::find */

template<class K, class E>
mypair< K, E>* hash_table<K,E>::find(const K& the_key, bool inserting) const
{
  // search the table
  int b = search(the_key,inserting);
  // see if a match was found at table[b]
  if (table[b] == NULL || table[b]->first != the_key)
    return NULL;    // no match
  return table[b];  // matching pair
}

/* = INSERTING =
 *
 * It begins by invoking the method search. If the returned bucket b is empty, then there is no
 * pair in the table with key the_pair.first and the pair the_pair may be inserted into this
 * bucket. If the returned bucket is not empty, then it either contains a pair with key the_pair.first
 * or the table is full. In the former case we change the second component of the pair stored 
 * in the bucket to the_pair.second; in the latter, we throw an exception
 */

template<class K, class E>
void hash_table<K,E>::insert( mypair<K, E>& the_pair)
{
  // search the table for a matching element
  int b = search(the_pair.first,true);
  // chack if matching element found
  if (table[b] == NULL){
    // no matching element and table not full
    table[b] = new mypair<K,E> (the_pair);
    dsize++;
  } else {
    // check id duplicate or table full
    if (table[b]->first == the_pair.first) 
      // duplicate, change table[b]->second
      table[b]->second = the_pair.second;
    else{
     resize();
     insert(the_pair);
    }
  }
}

template<class K, class E>
void hash_table<K,E>::insert(const K & k, const E & e )
{
  // search the table for a matching element
  int b = search(k,true);
  // chack if matching element found
  if (table[b] == NULL){
    // no matching element and table not full
    mypair<K,E> * pair = new mypair<K,E>(k,e);
    table[b] = pair;
    dsize++;
  } else {
    // check id duplicate or table full
    if (table[b]->first == k) 
      // duplicate, change table[b]->second
      table[b]->second = e;
    else{
      resize();
      insert(k,e);
    }
  }
}

template<class K, class E>
void hash_table<K,E>::insert(const K & k)
{
  // search the table for a matching element
  int b = search(k,true);
  // chack if matching element found
  if (table[b] == NULL){
    // no matching element and table not full
    mypair<K,E> * pair = new mypair<K,E>(k);
    table[b] = pair;
    dsize++;
  } else {
      resize();
      insert(k);
    }
}


template<class K, class E>
void hash_table<K,E>::erase(const K& k){
	int b = search(k);
	if(table[b]!= NULL){
		delete table[b];
		table[b] = NULL;
		erased[b] = true;
		dsize--;
	}
     
}

template<class K, class E>
void hash_table<K,E>::modify(const K& k, const E& e){
	int b = search(k);
	if (table[b] == NULL || table[b]->first != k)
    	return ;    // no match
    table[b]->second = e;
}

template <class K,class E>
bool hash_table<K,E>::containsValue(const E& e) const{
		int i = 0;
		int j = 0;
		while(j<dsize){
			if(table[i]!=NULL){
				if(table[i]->second == e )
					return true;
				j++;
			}
			i++;
		}
		return false;
}

template <class K,class E>
Linked_list<E> hash_table<K,E>::values() const {
		int i = 0;
		int j = 0;
		Linked_list<E> l;
		while(j<dsize){
			if(table[i]!=NULL){
				l.push_back(table[i]->second);
				j++;
			}
			i++;
		}
		return l;
}

template <class K,class E>
Linked_list<K> hash_table<K,E>::keys() const {
		int i = 0;
		int j = 0;
		Linked_list<K> l;
		while(j<dsize){
			if(table[i]!=NULL){
				l.push_back(table[i]->first);
				j++;
			}
			i++;
		}
		return l;
}

template <class K,class E>
Linked_list<K> hash_table<K,E>::keys(const E & e) const {
		int i = 0;
		int j = 0;
		Linked_list<K> l;
		while(j<dsize){
			if(table[i]!=NULL ) {
				j++;
				if(  table[i]->second == e )
					l.push_back(table[i]->first);
			}
			i++;
		}
		return l;
}

template <class K,class E>
void hash_table<K,E>::resize() {
	
	hash_table<K,E> support(divisor*2);

	int i = 0;
	int j = 0;
	while(j<dsize){
		if(table[i]!=NULL){
			support[table[i]->first] = table[i]->second;
			j++;
			}
		i++;
	}
	*this = support;
}
// four methods to scan linearly the hash table
template <class K,class E>
K & hash_table<K,E>::read_key(int i) const { 
	if(i<divisor && table[i]  != NULL)
		return table[i]->first;
}

template <class K,class E>
E & hash_table<K,E>::read_value(int i) const { 
	if(i<divisor && table[i]  != NULL)
		return table[i]->second;
}

template <class K,class E>
int hash_table<K,E>::next(int i) const { 
	i++;
	while(i<divisor && table[i]  == NULL)
		i++;
	if(i<divisor)
		return i;
	else return -1;
}

template <class K,class E>
bool hash_table<K,E>::end(int i) const { 
	return (i == -1);
}

template<class K, class E>
hash_table<K,E> & hash_table<K,E>::operator= (const hash_table<K,E> & h){
	if(&h != this) {
		divisor = h.divisor;
		if(table != 0x0)
			delete[] table;
		if(erased !=0x0)
			delete[] erased;
		table = new mypair<K,E> * [divisor];
		erased = new bool [divisor];
		dsize = h.dsize;
		mypair<K,E> * pair;
		for(int i = 0;i<divisor;i++) {
				if(h.table[i] == NULL)
				table[i] = NULL;
			else {
				pair = new mypair<K,E>;
				pair->first = h.table[i]->first; 
				pair->second = h.table[i]->second; 
				table[i] = pair;
			}
			erased[i] = h.erased[i];
		}
	}
	return *this;
}

template<class K, class E>
hash_table<K,E> & hash_table<K,E>::operator= ( hash_table<K,E> && h) {
	divisor = h.divisor;
	if(table != 0x0)
		delete[] table;
	if(erased !=0x0)
		delete[] erased;
	table = new mypair<K,E> * [divisor];
	erased = new bool [divisor];
	dsize = h.dsize;
	mypair<K,E> * pair;
	for(int i = 0;i<divisor;i++) {
		if(h.table[i] == NULL)
			table[i] = NULL;
		else {
			pair = new mypair<K,E>;
			pair->first = h.table[i]->first; 
			pair->second = h.table[i]->second; 
			table[i] = pair;
		}
		erased[i] = h.erased[i];
	}
	return *this;
}
	


template<class K, class E>
bool hash_table<K,E>::operator == ( const hash_table<K,E> & h) {
	if(dsize!=h.dsize)
		return false;
	int i=0;
	mypair<K,E> * pair;
	while(i<divisor) {
		if(h.table[i] != NULL) {
			pair = find(h.table[i]->first);
			if(pair==NULL)
				return false;
			else 
				if(pair->second != h.table[i]->second)
					return false;
					
		}
		i++;
	}
	return true;
}

template<class K, class E>
E & hash_table<K,E>::operator[](K i) { 
	if(find(i,true)==NULL) 
		insert(i); 
	return find(i)->second;
 }

template<class K, class E>
E hash_table<K,E>::operator[](K i) const { 
	if(find(i)==NULL) 
		insert(i); 
	return find(i)->second;
 }

#endif
