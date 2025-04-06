#ifndef HASHTABLE_H
#define HASHTABLE_H

#include <iostream>
#include <string>
#include <utility>  // For std::pair
#include <cstring>  // For memset
using namespace std;

class HashTable {
    private:
        pair<string, int>** table; // array of pointers to array of pairs
        int tableSize;
        int* chainSizes;
        int elementCount;
        float threshold;

        int hash(const string& key) const;
        void resizeTable();

    public: 
        HashTable(int size, float loadFactorThreshold); 
        ~HashTable();                 

        void insert(const string& key, int value);

        bool search(const string& key, int& value) const;

        bool remove(const string& key);

        void printTable() const;
};

#endif 
