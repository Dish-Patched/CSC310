#include "avl.h"

AVLTree::AVLTree()
{
    root = nullptr;
}

AVLTree::~AVLTree()
{
    destroyTree(root);
}

Node* AVLTree::insertNode(Node* node, int key)
{
    // normal BST insertion
    if (node == nullptr)
        return new Node(key);

    if (key < node->key)
        node->left = insertNode(node->left, key);
    else if(key > node->key)
        node->right = insertNode(node->right, key);
    else
        return node;

    // updating root node height
    node->height = max(height(node->left), height(node->right)) + 1;

    int balance = getBalanceFactor(node);

    // Left Left Case 
    if (balance > 1 && key < node->left->key) 
        return rotateRight(node); 

    // Right Right Case 
    if (balance < -1 && key > node->right->key) 
        return rotateLeft(node); 

    // Left Right Case 
    if (balance > 1 && key > node->left->key) { 
        node->left = rotateLeft(node->left); 
        return rotateRight(node); 
    } 

    // Right Left Case 
    if (balance < -1 && key < node->right->key) { 
        node->right = rotateRight(node->right); 
        return rotateLeft(node); 
    }
    
    return node;
}

void AVLTree::insert(int key)
{
    root = insertNode(root, key);
}

Node* AVLTree::minValueNode(Node* node)
{
    Node* current = node;

    while(current->left != nullptr)
        current = current->left;

    return current;
}

Node* AVLTree::removeNode(Node* root, int key)
{
    if (root == nullptr)
        return root;

    if (key < root->key)
        root->left = removeNode(root->left, key);
    else if (key > root->key)
        root->right = removeNode(root->right, key);
    else
    {
        if (root->left == nullptr || root->right == nullptr)   // one or no children
        {
            Node* temp = nullptr;

            if (root->left)
                temp = root->left;
            else if (root->right)
                temp = root->right;

            if (temp == nullptr)   // no children
            {
                temp = root;
                root = nullptr;
            }
            else  // one child
            {
                *root = *temp;
            }

            delete temp;
        }
        else  // two children
        {
            Node* temp = minValueNode(root->right);
            root->key = temp->key;
            root->right = removeNode(root->right, temp->key);
        }
    }

    if (root == nullptr)
        return root;

    // updating root node height
    root->height = max(height(root->left), height(root->right)) + 1;

    int balance = getBalanceFactor(root);

     // Left Left Case
     if (balance > 1 && 
        getBalanceFactor(root->left) >= 0)
        return rotateRight(root);

    // Left Right Case
    if (balance > 1 && 
        getBalanceFactor(root->left) < 0) {
        root->left = rotateLeft(root->left);
        return rotateRight(root);
    }

    // Right Right Case
    if (balance < -1 && 
        getBalanceFactor(root->right) <= 0)
        return rotateLeft(root);

    // Right Left Case
    if (balance < -1 && 
        getBalanceFactor(root->right) > 0) {
        root->right = rotateRight(root->right);
        return rotateLeft(root);
    }

    return root;
}

void AVLTree::remove(int key)
{
    root = removeNode(root, key);
}

void AVLTree::destroyTree(Node* node)
{
    if(node)
    {
        destroyTree(node->left);
        destroyTree(node->right);
        delete node;
    }
}

int AVLTree::height(Node* node)
{
    if(node)
        return node->height;
    else
        return -1;
}

int AVLTree::getBalanceFactor(Node* node)
{
    if(node)
        return height(node->left) - height(node->right);
    else
        return 0;
}

Node* AVLTree::rotateRight(Node* y)
{
    Node* x = y->left;
    Node* T2 = x->right;
    
    x->right = y;
    y->left = T2;

    y->height = max(height(y->left), height(y->right)) + 1;
    x->height = max(height(x->left), height(x->right)) + 1;

    return x;
}

Node* AVLTree::rotateLeft(Node* y)
{
    Node* x = y->right;
    Node* T2 = x->left;
    
    x->left = y;
    y->right = T2;

    y->height = max(height(y->left), height(y->right)) + 1;
    x->height = max(height(x->left), height(x->right)) + 1;

    return x;
}

void AVLTree::printTree(Node* root, int space)
{
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

void AVLTree::print()
{
    cout << endl;
    printTree(root, 0);
    cout << endl;
}