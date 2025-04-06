#include "hash.h"

HashTable::HashTable(int size, float loadFactorThreshold) {
    tableSize = size;
    elementCount = 0;
    threshold = loadFactorThreshold;
    table = new vector<pair<string, int>>[tableSize];
}

HashTable::~HashTable() {
    delete[] table;
}

int HashTable::hash(const string& key){
    int hashValue = 0;
    for (char c : key) {
        hashValue = (hashValue * 31 + c) % tableSize;  
    }
    return hashValue;
}

void HashTable::insert(const string& key, int value) {
    float alpha = (float)(elementCount + 1) / tableSize;
    if(alpha > threshold)
        resizeTable();

    int index = hash(key);
    table[index].push_back(make_pair(key, value));
    elementCount++;

}

bool HashTable::search(const string& key, int& value){
    int index = hash(key);
    for (const auto& pair : table[index]) {
        if (pair.first == key) {
            value = pair.second;
            return true;
        }
    }
    return false;
}

bool HashTable::remove(const string& key) {
    int index = hash(key);
    auto& listAtIndex = table[index];
    for (auto it = listAtIndex.begin(); it != listAtIndex.end(); ++it) {
        if (it->first == key) {
            listAtIndex.erase(it);
            elementCount--;
            return true;
        }
    }
    return false;
}

void HashTable::resizeTable() {
    int oldTableSize = tableSize;
    tableSize *= 2;
    
    // Create a new table
    vector<pair<string, int>>* newTable = new vector<pair<string, int>>[tableSize];

    // Rehash all elements from the old table into the new table
    for (int i = 0; i < oldTableSize; ++i) {
        for (const auto& pair : table[i]) {
            int newIndex = hash(pair.first);
            newTable[newIndex].push_back(pair);
        }
    }

    // Delete the old table and assign the new one
    delete[] table;
    table = newTable;

    cout << "Table resized to " << tableSize << " slots." << endl;
}

void HashTable::printTable(){
    for (int i = 0; i < tableSize; ++i) {
        cout << i << ": ";
        if (!table[i].empty()) {
            for (const auto& pair : table[i]) {
                cout << "(" << pair.first << ", " << pair.second << ") -> ";
            }
            cout << "NULL";
        } else {
            cout << "NIL";
        }
        cout << endl;
    }
}
