#pragma once
#include <string>
#include <iostream>
#include "LinkedList.h"
using namespace std;
const int TableSize = 12697;  // Table size for the hash table

// Forward declaration of T (could be any data type like UserNode, Product, etc.)
template <typename T>
class HashTable {
private:
    // Array of pointers to type T (e.g., UserNode, Product)
    int numberOfElements;


public:
    LinkedList<T> buckets[TableSize];
    //make it T
    HashTable();
    ~HashTable();
    void insert(T* to_add, int sum);
    int hash(int sum) const;  // Hash function
    int getnumberofelments();
    //T* table[TableSize];

};

// Implementation of the hash function
template <typename T>
int HashTable<T>::hash(int sum) const {
    return sum % TableSize;  // Simple modulus-based hash function
}

template<typename T>
inline int HashTable<T>::getnumberofelments()
{
    return numberOfElements;
}

// Constructor initializing the hash table
template <typename T>
HashTable<T>::HashTable() {
    numberOfElements = 0;
}
template <typename T>
HashTable<T>::~HashTable() {
    // Iterate over all the slots in the table
    for (int i = 0; i < TableSize; ++i) {
        buckets[i].clear();
    }
    numberOfElements = 0;
}


// Insert a node into the hash table
template <typename T>
void HashTable<T>::insert(T* to_add, int sum) {

    int index = hash(sum);
    buckets[index].append(to_add);
    numberOfElements++;
}
