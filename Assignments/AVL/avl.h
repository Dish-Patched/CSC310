#ifndef AVL_H
#define AVL_H

#include <iostream>
#include "customErrorClass.h"

using namespace std;

struct Node
{
    int key;
    Node* left;
    Node* right;
    int height;

    Node(int val)
    {
        key = val;
        left = nullptr;
        right = nullptr;
        height = 0;
    }
};

class AVLTree
{
    private:
        Node* root;

        Node* insertNode(Node* node, int key);
        Node* removeNode(Node* node, int key);
        Node* minValueNode(Node* node);

        int height(Node* node);
        int getBalanceFactor(Node* node);

        Node* rotateRight(Node* y);
        Node* rotateLeft(Node* x);

        void printTree(Node* root, int space);
        void destroyTree(Node* node);

    public:
        AVLTree();
        ~AVLTree();

        void insert(int key);
        void remove(int key);
        void print();

};

#endif