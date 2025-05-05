About: Implementing 2 versions of Kruskal's algorithm usign Binomial and Binary heaps
Date: Apr 22, 2025
Comments: Includes seven files -> binaryHeap.h, binomialHeap.h, mst.h, binaryHeap.cpp, binomialHeap.cpp, mst.cpp, main.cpp

*** FIRST OPEN THE FOLDER WHERE THESE THREE FILES ARE LOCATED:
    In command prompt:
        cd folder-containing-the-files
        code .
*** 
To compile: g++ binaryHeap.cpp binomialHeap.cpp mst.cpp main.cpp
To run: ./a 

OR

To compile: g++ binaryHeap.cpp binomialHeap.cpp mst.cpp main.cpp -o whatevernameyoulike
To run: ./whatevernameyoulike


Task 8:

Using a binomial heap improves efficiency mainly for merging heaps, but for standard Kruskal's algorithm, it performs similarly to a binary heap.

Union-find with path compression and union by size makes find and union operations nearly constant time, greatly speeding up Kruskal’s algorithm.

Timing shows that for small and medium graphs, both versions perform similarly; binomial heaps show slight improvement only for very large graphs.
The time complexity of both Kruskal versions is O(m log m), where m is the number of edges