#include "hash.h"

int HashTable::hash(const string& key) const {
    int hashValue = 0;
    for (char c : key) {
        hashValue = (hashValue * 31 + c) % tableSize;
    }
    return hashValue;
}

void HashTable::resizeTable() {
    int oldSize = tableSize;
    tableSize *= 2;

    // Create new table with double the size
    pair<string, int>** newTable = new pair<string, int>*[tableSize];
    int* newChainSizes = new int[tableSize];
    memset(newChainSizes, 0, sizeof(int) * tableSize);

    for (int i = 0; i < tableSize; ++i) {
        newTable[i] = nullptr;
    }

    // Rehash all elements into the new table
    for (int i = 0; i < oldSize; ++i) {
        if (table[i] != nullptr) {
            for (int j = 0; j < chainSizes[i]; ++j) {
                int newIndex = hash(table[i][j].first) % tableSize;

                // Add to new table
                if (newTable[newIndex] == nullptr) {
                    newTable[newIndex] = new pair<string, int>[1];
                    newTable[newIndex][0] = table[i][j];
                    newChainSizes[newIndex] = 1;
                } else {
                    // Resize the chain and add the new pair
                    int newSize = newChainSizes[newIndex];
                    pair<string, int>* newChain = new pair<string, int>[newSize + 1];

                    // Copy old chain elements
                    for (int k = 0; k < newSize; ++k) {
                        newChain[k] = newTable[newIndex][k];
                    }
                    newChain[newSize] = table[i][j];

                    // Free old chain memory
                    delete[] newTable[newIndex];
                    newTable[newIndex] = newChain;
                    newChainSizes[newIndex]++;
                }
            }

            // Free old chain memory
            delete[] table[i];
        }
    }

    // Free the old table and update the new one
    delete[] table;
    delete[] chainSizes;

    table = newTable;
    chainSizes = newChainSizes;

    cout << "Table resized to " << tableSize << " slots." << endl;
}


HashTable::HashTable(int size, float loadFactorThreshold)
    : tableSize(size), elementCount(0), threshold(loadFactorThreshold) {
    table = new pair<string, int>*[tableSize];
    chainSizes = new int[tableSize];
    memset(chainSizes, 0, sizeof(int) * tableSize);

    for (int i = 0; i < tableSize; ++i) {
        table[i] = nullptr;
    }
}

HashTable::~HashTable() {
    for (int i = 0; i < tableSize; ++i) {
        delete[] table[i];  // Free each chain
    }
    delete[] table;
    delete[] chainSizes;
}

void HashTable::insert(const string& key, int value) {
    float alpha = (float)(elementCount + 1) / tableSize;
    if (alpha > threshold) {
        resizeTable();
    }

    int index = hash(key);

    // Check for duplicates
    if (table[index] != nullptr) {
        for (int i = 0; i < chainSizes[index]; ++i) {
            if (table[index][i].first == key) {
                table[index][i].second = value;  // Update value
                return;
            }
        }
    }

    // Insert new element
    int newSize = chainSizes[index] + 1;
    pair<string, int>* newChain = new pair<string, int>[newSize];

    // Copy old chain elements
    for (int i = 0; i < chainSizes[index]; ++i) {
        newChain[i] = table[index][i];
    }

    // Add new element
    newChain[newSize - 1] = make_pair(key, value);

    // Free old chain memory
    delete[] table[index];

    table[index] = newChain;
    chainSizes[index]++;
    elementCount++;
}

bool HashTable::search(const string& key, int& value) const {
    int index = hash(key);

    if (table[index] != nullptr) {
        for (int i = 0; i < chainSizes[index]; ++i) {
            if (table[index][i].first == key) {
                value = table[index][i].second;
                return true;
            }
        }
    }
    return false;
}

bool HashTable::remove(const string& key) {
    int index = hash(key);

    if (table[index] != nullptr) {
        for (int i = 0; i < chainSizes[index]; ++i) {
            if (table[index][i].first == key) {
                    
                // Shift elements left
                for (int j = i; j < chainSizes[index] - 1; ++j) {
                    table[index][j] = table[index][j + 1];
                }

                chainSizes[index]--;

                // Resize the chain if necessary
                if (chainSizes[index] > 0) {
                    pair<string, int>* newChain = new pair<string, int>[chainSizes[index]];

                    for (int k = 0; k < chainSizes[index]; ++k) {
                        newChain[k] = table[index][k];
                    }

                    delete[] table[index];
                    table[index] = newChain;
                } else {
                    delete[] table[index];
                    table[index] = nullptr;
                }

                elementCount--;
                return true;
            }
        }
    }
    return false;
}

void HashTable::printTable() const {
    for (int i = 0; i < tableSize; ++i) {
        cout << i << ": ";
        if (table[i] != nullptr) {
            for (int j = 0; j < chainSizes[i]; ++j) {
                cout << "(" << table[i][j].first << ", " << table[i][j].second << ") -> ";
            }
            cout << "NULL";
        } else {
            cout << "NIL";
        }
        cout << endl;
    }
}

