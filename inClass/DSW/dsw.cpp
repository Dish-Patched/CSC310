#include "dsw.h"

// -------------------------------PRIVATE-------------------------------------

// when left heavy tree
void BST::rotateRight(Node*& node)  //passing the parent
{
    if(node == nullptr || node->left == nullptr)
        return;
    
    // get the node to rotate right
    Node* leftChild = node->left;
    // 1) leftnode's right child is going to become parent's left child
    node->left = leftChild->right
    // 2) parent is going to be the right child of node that is rotated
    leftChild->right = node;
    
    node = leftChild;
}

// when right-heavy
void BST::rotateLeft(Node*& node)
{
    if(node == nullptr || node->right == nullptr)
        return;

    // get the node to rotate left
    Node& rightChild = node->right;
    // 1) rightnode's left child is going to become parent's right child
    node->right = rightChild->left;
    // 2) parent is going to be left child of the node that is rotated
    rightChild->left = node;

    node = rightChild;
}


// Phase 1 - right skewed linked list tree
void BST::createVine()
{
    if(root == nullptr)
        return;

    Node* grandparent = nullptr;
    Node* parent = root;
    Node* child = root->left;

    while(parent != nullptr)
    {
        if(child != nullptr)   // There is left child => Rotate Right
        {
            rotateRight(parent);
            if(grandparent == nullptr)
                root = parent;
            else   
                grandparent->right = parent;
            child = parent->left;
        }
        else   // no left child => just keep moving right
        {
            grandparent = parent;
            parent = parent->right;
            if(parent != nullptr)
                child = parent->left;
        }
    }
}

void BST::rebuildTree(int size)
{
    // how many left rotations
    //initial rotation
    int highestPowerof2 = (int)pow(2, log2(size+1));
    int m = (size + 1) - highestPowerof2;

    performRotations(m);

    // Subsequent Rotations
    for(size = (size - m) / 2; size > 0; size /= 2)
        performRotations(size);
}

// left rotate every second node based count
void BST::performRotations(int count)
{
    Node* grandparent = nullptr;
    Node* parent = root;
    Node* child = root->right;

    for(int i = 0; i < count; i++)
    {
        if(child == nullptr)
            break;
        
        rotateLeft(parent);
        if(grandparent == nullptr)
            root = parent;
        else
            grandparent->right = parent;

        grandparent = parent;
        parent = parent->right;
        if(parent != nullptr)
            child = parent->left;
    }
}

void BST::printTree(Node* root, int space)
{

}

// -------------------------- PUBLIC ----------------------------------

BST::BST()
{
    root = nullptr;
}

BST::~BST()
{
    deleteTree(root);
}

void BST::deleteTree(Node*& node)
{
    if(node == nullptr)
        return;

    deleteTree(node->left);
    deleteTree(node->right);

    delete node;
}

void BST::insert(int val)
{
    Node* newNode = new Node(val);
    if(root == nullptr)
    {
        root = newNode;
        return;
    }

    Node* curr = root;
    Node* parent = nullptr;

    while(curr != nullptr)
    {
        parent = curr;
        if(val < curr->data)
            curr = curr->left;
        else
            curr = curr->right;
    }

    if(val < parent->data)
        parent->left = newNode;
    else    
        parent->right = newNode;
}

void BST::dswBalance()
{
    if(root == nullptr)
        return;

    createVine();

    cout << "After Phase 1: ";
    display();

    int size = 0;
    Node* temp = root;
    while(temp != nullptr)
    {
        size++;
        temp = temp->right;
    }

    rebuildTree(size);
}

void BST::display()
{
    cout << endl;
    printTree(root, 0);
    cout << endl;
}