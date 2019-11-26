#ifndef _DICTIONARY_H
#define _DICTIONARY_H

template<class K, class E>
class mypair {
  // data member
  public:
  K first;
  E second;

  // methods
	mypair(){}
	mypair(mypair<K,E>& the_pair){
    	first = the_pair.first;
    	second = the_pair.second;
  	}
	mypair(const K & k, const E & e){
    	first = k;
    	second = e;
  	}
  	mypair(const K & k){
    first = k;
  	}
};


template <class K, class E>
class dictionary
{

public:
  virtual ~dictionary() {}
  
  virtual void create() = 0;		
      // create an empty dictionary
  virtual bool empty() const = 0;	
      // return true off the dictionary is empty
  virtual int size() const = 0;		
      // return the number of pairs in the dictionary
  virtual mypair< K, E>* find(const K& k, bool inserting) const = 0;	
      // return the pair with key k
  virtual void insert( mypair< K, E>& p) = 0;		
      // insert the pair p into the dictionary
  virtual void erase(const K& k) = 0;	
      // delete the pair with key k
  virtual void modify(const K& k, const E& e) = 0;
      // modify the value of the pair with key k to e
};

#endif
