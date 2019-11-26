#ifndef _HASHING_
#define _HASHING_

#include <iostream>

using std::string;

template<class T>
class hash{
public:
  size_t operator()(const T the_key) const;
};


/* a specialization with type string */
template<>
class hash<string>
{
public:
  size_t operator()(const string the_key) const {
    unsigned long hash_value = 0;
    int length = (int) the_key.length();
    for (int i=0; i<length; i++)
      hash_value = 5 * hash_value + the_key.at(i);
    return size_t(hash_value);
  }
};

template<>
class hash<int>
{
public:
  size_t operator()(const int the_key) const {
    if(the_key>=0) //Determina una funzione bigettiva tra i numeri interi e i numeri interi positivi
    	return the_key*2;
    else return the_key*(-2)+1;
  }
};

template<>
class hash<char>
{
public:
  size_t operator()(const char the_key) const {
    return (size_t)the_key;
  }
};
/* = LINEAR PROBING = 
 *
 * The easiest way to find a place to put a value in the table is to search the table for 
 * the next available bucket.
 *
 * On the other side, the search begins at the home bucket f(k) of the key k we are searching
 * for and continues by examining successive buckets in the table until one of the following
 * conditions happens:
 *   i) a bucket containing a pair with key k is reached
 *  ii) an empty bucket is reached
 * iii) we return to the home bucket
 */


#endif
