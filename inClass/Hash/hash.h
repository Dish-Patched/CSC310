#ifndef HASHTABLE_H
#define HASHTABLE_H

#include <iostream>
#include <string>
#include <vector>    // resizable arrays
#include <iterator>

class HashTable
{
    private:
        vector<pair<string, int>>* table;   // array of vectors
        int tableSize;
        int elementCount;
        int threshold;

        int hash(const string& key);
        void resizeTable();

    public:
        HashTable(int size, float loadFactorThreshold);
        ~HashTable();

        void insert(const string& key, int value);
        bool search(const string& key, int value);
        void remove(const string& key);

        void printTable();
};

using namespace std;

#endif