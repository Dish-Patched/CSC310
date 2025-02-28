#include "rb.h"

// +++++++++++++++++++++++++++++++ PUBLIC ++++++++++++++++++++++++++++++++++++++++++

RBTREE::RBTREE()
{
    TNULL = new Node(0);
    TNULL->color = BLACK;
    // TNULL->left = nullptr;
    // TNULL->right = nullptr;
    // TNULL->parent = nullptr;
    root = TNULL;
}

RBTREE::~RBTREE()
{
    deleteSubtree(root);
    delete TNULL;
}

void RBTREE::insert(int key)
{
    Node* node = new Node(key);
    // node->data = key;
    node->left = TNULL;
    node->right = TNULL;
    // node->parent = nullptr;
    // node->color = RED;

    if(root == TNULL)
    {
        root = node;
        root->color = BLACK;
        return;
    }

    insertR(root, node);
    insertFix(node);
}

void RBTREE::remove(int key)
{
    root = removeR(root, key);
}

void RBTREE::printTree()
{
    if(root == TNULL)
    {
        cout << "Tree is empty" << endl;
        return;
    }
    print(root, 0);
}


// ++++++++++++++++++++++++++++++++++ PRIVATE +++++++++++++++++++++++++++++++++++

void RBTREE::leftRotate(Node* y)
{
    Node* x = y->right;
    y->right = x->left; // adoption

    if(x->left != TNULL)     // updating parent of updated left child
        x->left->parent = y;

    //update parent of x
    x->parent = y->parent;
    if(y->parent == nullptr)
        root = x;
    else if(y == y->parent->left)
        y->parent->left = x;
    else
        y->parent->right = x;

    x->left = y;
    y->parent = x;
}

void RBTREE::rightRotate(Node* y)
{
    Node* x = y->left;
    y->left = x->right; // adoption

    if(x->right != TNULL)     // updating parent of right left child
        x->right->parent = y;

    //update parent of x
    x->parent = y->parent;
    if(y->parent == nullptr)
        root = x;
    else if(y == y->parent->right)
        y->parent->right = x;
    else
        y->parent->left = x;

    x->right = y;
    y->parent = x;
}

void RBTREE::insertR(Node*& root, Node*& node)
{
    if(root == TNULL)
    {
        root = node;
        return;
    }

    if(node->data < root->data)
    {
        if(root->left == TNULL)
        {
            root->left = node;
            node->parent = root;
        }
        else
        {
            insertR(root->left, node);
        }
    }
    else
    {
        if(root->right == TNULL)
        {
            root->right = node;
            node->parent = root;
        }
        else
        {
            insertR(root->right, node);
        }
    }
}

void RBTREE::insertFix(Node* k)
{
    Node* uncle;

    // always when parent is RED - violates property 3
    while(k->parent->color == RED)
    {
        // Parent is right child
        if(k->parent == k->parent->parent->right)
        {
            uncle = k->parent->parent->left;
            // CASE 2 - Red Uncle
            if(uncle->color == RED)
            {
                uncle->color = BLACK;
                k->parent->color = BLACK;
                k->parent->parent->color = RED;
                // update k if there are any new violations up the tree
                k = k->parent->parent;
            }
            else  // uncle is black
            {
                if(k == k->parent->left)  // CASE 3 - triangle case
                {
                    k = k->parent;
                    rightRotate(k);
                }
                // CASE 4 - line case
                k->parent->color = BLACK;
                k->parent->parent->color = RED;
                leftRotate(k->parent->parent);
            }
        }
        else  // parent is left child (mirror image of the previous one)
        {
            uncle = k->parent->parent->right;
            // CASE 2: RED uncle
            if(uncle->color == RED)
            {
                uncle->color = BLACK;
                k->parent->color = BLACK;
                k->parent->parent->color = RED;
                k = k->parent->parent;
            }
            else  // case 3
            {
                if(k == k->parent->right)
                {
                    k = k->parent;
                    leftRotate(k);
                }
                // case 4
                k->parent->color = BLACK;
                k->parent->parent->color = RED;
                rightRotate(k->parent->parent);
            }
        }
        if(k == root)
        {
            break;
        }
    }

    root->color = BLACK;
}

Node* RBTREE::removeR(Node* node, int key)
{
    if(node == TNULL)
    {
        cout << "Key not found in tree" << endl;
        return node;
    }

    if(key < node->data)
        node->left = removeR(node->left, key);
    else if(key > node->data)
        node->right = removeR(node->right, key);
    else
    {
        Node* y = node;  // node to be deleted
        Node* x;  // our replacement for the deleted node
        Color y_original_color = y->color;

        if(node->left == TNULL)   // CASE 1
        {
            x = node->right;
            transplant(node, node->right);
        }
        else if(node->right == TNULL)  // CASE 2
        {
            x = node->left;
            transplant(node, node->left);
        } 
        else  // CASE 3
        {
            y = successor(node->right);
            y_original_color = y->color;
            x = y->right;  // right child of successor

            if(y->parent != node)
            {
                transplant(y, y->right);
                y->right = node->right;
                y->right->parent = y;
            }

            transplant(node, y);
            y->left = node->left;
            y->left->parent = y;
            y->color = node->color;
        }
        delete node;
        if(y_original_color == BLACK)
        {
            deleteFix(x);
        }
    }

    return root;
}