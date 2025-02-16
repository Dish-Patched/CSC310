#ifndef DSW_H
#define DSW_H

#include <iostream>
#include <math.h>

using namespace std;

struct Node
{
    int data;
    Node* left;
    Node* right;

    Node(int val)
    {
        data = val;
        left = nullptr;
        right = nullptr;
    }
};

class BST
{
    private:
        Node* root;

        // helper functions
        void rotateRight(Node*& node);
        void rotateLeft(Node*& node);
        void createVine();   // Phase 1
        void rebuildTree(int size);   // Phase 2
        void performRotations(int count);   //helper for phase 2 (rebuildTree)
        void printTree(Node* root, int space);  

    public:
        BST();
        ~BST();
        // helper for the destructor
        void deleteTree(Node*& root);

        void insert(int val);
        void dswBalance();

        void display();
};

#endif