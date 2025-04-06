#ifndef HASHTABLE_H
#define HASHTABLE_H

#include <iostream>
#include <vector>
#include <string>
#include <iterator>

using namespace std;

class HashTable {
    private:
        vector<pair<string, int>>* table;
        int tableSize;
        int elementCount;
        float threshold;

        int hash(const string& key);
        void resizeTable();

    public: 
        HashTable(int size, float loadFactorThreshold); 
        ~HashTable();                 

        void insert(const string& key, int value);

        bool search(const string& key, int& value);

        bool remove(const string& key);

        void printTable();
};

#endif 
