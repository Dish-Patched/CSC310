#include <iostream>
#include "hash.h"

int main() {
    // Create a hash table of size 10
    // HashTable ht(10);
    HashTable ht(5, 0.75);

    // Insert key-value pairs
    ht.insert("Alice", 25);
    ht.insert("Bob", 30);
    ht.insert("Charlie", 35);
    ht.insert("David", 40);
    ht.insert("Eve", 45);

    // Print the hash table
    cout << endl << "Hash Table after insertions:" << endl;
    ht.printTable();

    // Search for a value
    int value;
    if (ht.search("Alice", value)) {
        cout << endl << "Found Alice with value: " << value << endl;
    } else {
        cout << endl << "Alice not found!" << endl;
    }

    // Remove a key-value pair
    if (ht.remove("Bob")) {
        cout << endl << "Bob removed from the hash table." << endl;
    } else {
        cout << endl << "Bob not found to remove!" << endl;
    }

    // Print the hash table again
    cout << endl << "Hash Table after removal:" << endl;
    ht.printTable();

    return 0;
}
