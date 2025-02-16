#include "splay.h"

SplayTree::SplayTree() 
{
    root = nullptr; 
}

// aka Zig
SplayTree::Node* SplayTree::rotateRight(Node* x) {
    Node* y = x->left;
    x->left = y->right;
    y->right = x;
    return y;
}

// aka Zag
SplayTree::Node* SplayTree::rotateLeft(Node* x) {
    Node* y = x->right;
    x->right = y->left;
    y->left = x;
    return y;
}

// Splaying :)
SplayTree::Node* SplayTree::splay(Node* root, int key) {
    // complete this
    if(root == nullptr || root->key == key){
        //throw MyException("Tree is empty.");
        return root;
    }

    // for zig
    if(key < root->key)
    {
        if(root->left == nullptr)
            return root;

        if(key < root->left->key)
        {
            root->left->left = splay(root->left->left, key);
            root = rotateRight(root);
        }
        else if(key > root->left->key)
        {
            root->left->right = splay(root->left->right, key);
            if(root->left->right != nullptr)
                root->left = rotateLeft(root->left);
        }
        

        if(root->left == nullptr)
            return root;
        
        return rotateRight(root);
    }
    // for zag
    else 
    {
        if(root->right == nullptr)
            return root;

        if(key > root->right->key)
        {
            root->right->right = splay(root->right->right, key);
            root = rotateLeft(root);
        }
        else if(key < root->right->key)
        {
            root->right->left = splay(root->right->left, key);
            if(root->right->left != nullptr)
                root->right = rotateRight(root->right);
        }

        if(root->right == nullptr)
            return root;

        return rotateLeft(root);
    }
}


SplayTree::Node* SplayTree::insertNode(Node* root, int key) {
    // complete this
    if(root == nullptr){
        //throw MyException("Tree is empty");
        return new Node(key);
    }

    Node* current = root;
    Node* parent = nullptr;

    while(current != nullptr)
    {
        parent = current;

        //traversing tree for the node
        if(key < current->key)
            current = current->left;
        else if(key > current->key)
            current = current->right;
        else
            return splay(root, key);    // if the key already exists in the tree
    }

    Node* newNode = new Node(key);

    if(key < parent->key)
        parent->left = newNode;
    else
        parent->right = newNode;


    return splay(root, key);

}


SplayTree::Node* SplayTree::deleteNode(Node* root, int key) {
    // complete this
    if (root == nullptr) {
        throw MyException("Tree is empty.");
    }
    
    root = splay(root, key);
    
    if (root->key != key) {
        return root;
    }
    
    // node found, now delete it
    Node* temp = root;
    
    if (root->left == nullptr) {
        // no left child
        root = root->right;
    }
    else if (root->right == nullptr) {
        // no right child
        root = root->left;
    }
    else {
        // both children exist
        Node* leftTree = root->left;
        leftTree = splay(leftTree, key);  // this brings the largest node to the root
        
        // connecting the trees
        leftTree->right = root->right;
        
        root = leftTree;
    }
    
    delete temp;
    
    return root;
}


void SplayTree::insert(int key) {
    root = insertNode(root, key);
}


void SplayTree::remove(int key) {
    root = deleteNode(root, key);
}


bool SplayTree::search(int key) {
    root = splay(root, key);
    return (root && root->key == key);
}


void SplayTree::printTree(Node* root, int space) {
    const int COUNT = 10;  

    if (root == nullptr) {
        return;
    }

    // Increase the distance between levels
    space += COUNT;

    // Print the right child first (to appear on top)
    printTree(root->right, space);

    // Print the current node after right child

    for (int i = COUNT; i < space; i++) {
        cout << " "; // Indentation for tree depth
    }
    cout << root->key << endl;

    // Print the left child
    printTree(root->left, space);
}

void SplayTree::display() {
    printTree(root, 0);
    cout << endl;
}
