About: Benchmarking Hash Tables using different types of chaining, open addressing and also using standard C++ unordered map
Date: Apr 6, 2025
Comments: Includes three files -> hash.h, AVL/avl.cpp, mainHash.cpp

*** FIRST OPEN THE FOLDER WHERE THESE THREE FILES ARE LOCATED:
    In command prompt:
        cd folder-containing-the-files
        code .
*** 
To compile: g++ hash.cpp mainHash.cpp AVL/avl.cpp
To run: ./a 

OR

To compile: g++ mainHash.cpp hash.cpp AVL/avl.cpp -o whatevernameyoulike
To run: ./whatevernameyoulike


Task 6:

Best for insertion: Linear Probing was the fastest.

Best for search: Chaining with BST performed best.

Best for deletion: Linear Probing had the fastest deletions.

Best for low collisions: Linear Probing and Quadratic Probing are best when collision rates are low.

Best for high collisions: Quadratic Probing and Double Hashing handle collisions better than linear probing but at the cost of slower insertion times.

Best all-around option: std::unordered_map 