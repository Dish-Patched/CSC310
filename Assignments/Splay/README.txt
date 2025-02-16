About: Implementing Splay Trees using exception handling and makefiles
Date: Feb 13, 2025
Comments: Includes 5 files -> splay.h, splay.cpp, mainsplay.cpp, customErrorClass.h, customErrorClass.cpp

*** FIRST OPEN THE FOLDER WHERE THESE THREE FILES ARE LOCATED:
    In command prompt:
        cd folder-containing-the-files
        code .
***
To compile: g++ mainsplay.cpp splay.cpp customErrorClass.cpp
To run: ./a.out

OR

To compile: g++ mainsplay.cpp splay.cpp customErrorClass.cpp -o whatevernameyoulike
To run: ./whatevernameyoulike

Answer for Task 5:
Splaying ensures that the frequently accessed nodes are always at the top which reduces access time for those nodes. Even if the tree gets deep after many individual operations momentarily, it will get flattened over time due to the splaying operations.

Even though in the worst case, splaying may take O(n) time, the amortized cost becomes O(log n) because of the fact that the most frequently accessed nodes can be reached faster which reduces the cost of the operation for such operations lowering the amortized cost.