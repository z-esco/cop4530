#ifndef HASHTABLE_H
#define HASHTABLE_H
#include <vector>
#include <list>
#include <algorithm>
#include <iostream>
#include <fstream>

namespace cop4530{
// max_prime is used by the helpful functions provided to you.
static const unsigned int max_prime = 1301081;
// the default_capacity is used if the initial capacity 
// of the underlying vector of the hash table is zero. 
static const unsigned int default_capacity = 11;

void Menu();


template <typename K, typename V>
class HashTable{
    public:
        HashTable(int vSize = prime_below(101));//constructs table of vSize
        ~HashTable(); // destructor
        bool contains(const K& k) const; //checks if k is in table
        bool match(const std::pair<K,V> &kv) const;//check if key-value is in table
        bool insert(const std::pair<K,V> &kv);//adds kv to table
        bool insert(std::pair<K,V> &&kv);//move version of insert
        bool remove(const K & k);//delete k and corresponding value
        void clear();//deletes all elements
        bool load(const char* filename);//load content of filename
        void dump() const; //displays all entries in table
        int size() const ; // returns size of table
        bool write_to_file(const char* filename);//writes all elements in table to filename

    private:
        std::vector<std::list<std::pair(<K>,<V>)> vect[default_capacity];
        int vSize;

        void makeEmpty();//private version of clear
        void rehash();//called when vector is longer than hash table
        int myhash(const K &k) const;//retunr index of vector where k should be
        unsigned long prime_below (unsigned long n);
        void setPrimes(std::vector<unsigned long>& vprimes);

};
#include "hashtable.hpp"
}
#endif
