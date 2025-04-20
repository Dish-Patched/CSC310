#include "binomial.h"

int main() {
    BinomialHeap bh;
    bh.insert(10);
    bh.insert(20);
    bh.insert(5);
    bh.insert(30);
    bh.insert(1);
    bh.insert(14);
    bh.insert(27);
    bh.insert(8);
    bh.insert(3);
    bh.insert(12);
    
    cout << "Heap after insertions:" << endl;
    bh.printHeap();

    bh.deleteMin();

    cout << "Heap after deleting minNode:" << endl;
    bh.printHeap();

    bh.deleteKey(8);

    cout << "Heap after deleting 27:" << endl;
    bh.printHeap();

    return 0;
}