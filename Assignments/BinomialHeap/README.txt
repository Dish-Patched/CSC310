About: A binomial Heap implementation
Date: Apr 20, 2025
Comments: Includes three files -> binomial.h, binomial.cpp, main.cpp

*** FIRST OPEN THE FOLDER WHERE THESE THREE FILES ARE LOCATED:
    In command prompt:
        cd folder-containing-the-files
        code .
*** 
To compile: g++ binomial.cpp main.cpp
To run: ./a 

OR

To compile: g++ main.cpp binomial.cpp -o whatevernameyoulike
To run: ./whatevernameyoulike

Task 6:

1. Binomial heaps have better merging because it merges two heaps in sorted order which saves time and also only allows at most one binomial tree of degree k by linking the trees of same degrees

2. All operations have a time complexity of O(log n) 

3. Using left-child right sibling ensures each tree in the binomial heap is a binomial tree