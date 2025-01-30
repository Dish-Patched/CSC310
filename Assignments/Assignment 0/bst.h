#include<iostream>

using namespace std;

template<class Type>
struct Node
{
    Type info;
    Node<Type>* llink;
    Node<Type>* rlink;
};

template<class Type>
class BinarySearchTree 
{
protected:
    Node<Type>* root;
public:
    BinarySearchTree();
    void insertNode(const Type&);
    void deleteNode(const Type&);
    bool search(const Type&);
    void inorderTraversal();
    void preorderTraversal();
    void postorderTraversal();
    bool treeState();
    int treeHeight();
    ~BinaryTree();
private:
    void inorder(Node<Type>*);
    void preorder(Node<Type>*);
    void postorder(Node<Type>*);
    int height(Node<Type>*);
    void deleteFromTree(Node<Type>*&);
    Type sum(Node<Type>*);
    Type max(Type, Type);
};