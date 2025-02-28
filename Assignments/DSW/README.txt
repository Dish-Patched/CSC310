About: Implementing Self Balancing BST using DSW algorithm using exception handling and makefiles
Date: Feb 26, 2025
Comments: Includes 5 files -> dsw.h, dsw.cpp, main.cpp, customErrorClass.h, customErrorClass.cpp

*** FIRST OPEN THE FOLDER WHERE THESE THREE FILES ARE LOCATED:
    In command prompt:
        cd folder-containing-the-files
        code .
***
To compile: g++ mains.cpp dsw.cpp customErrorClass.cpp
To run: ./a.out

OR

To compile: g++ main.cpp dsw.cpp customErrorClass.cpp -o whatevernameyoulike
To run: ./whatevernameyoulike

Task 5:

1. This implementation is different because we make a partially left skewed vine to reduce the number of rotations hence reducing the time complexity

2. Phase 1 creates a partially left skewed vine which reserves the position of the nodes that do not need to be rotated

3. Phase 2 is faster because of the height balancing being less strict which makes the tree faster for dynamic operations

4. The balancing is faster but the search operation is slower which means the tree is not perfectly balanced

5. Another variation could be where the tree self balances only when the height surpasses the 2log2(N) limitation
