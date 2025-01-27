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
    bool balancedTree();
    int treeHeight();
    ~BinaryTree();
private:
    void inorder(Node<Type>*);
    void preorder(Node<Type>*);
    void postorder(Node<Type>*);
    int height(Node<Type>*);
    void deleteFromTree(Node<Type>*&);
};

template<class Type>
BinarySearchTree<Type>::BinarySearchTree()
{
    root = NULL;
}

template<class Type>
void BinarySearchTree<Type>::insertNode(const Type& x)
{
    Node<Type>* current, *prevCurrent=NULL, *newNode;
    newNode = new Node<Type>;
    newNode->info = x;
    newNode->llink = NULL;
    newNode->rlink = NULL;
    if(this->root == NULL){
        this->root = newNode;
    }
    else{
        current = this->root;
        while(current != NULL){
            prevCurrent = current;
            if(current->info == x){
                cout << "Node already exists" << endl;
                return;
            }
            else{
                if(current->info > x)
                    current = current->llink;
                else    
                    current = current->rlink;
            }
        if(prevCurrent->info > x)
            prevCurrent->llink = newNode;
        else
            prevCurrent->rlink = newNode;
        }
    }
}


template<class Type>
void BinarySearchTree<Type>::deleteFromTree(Node<Type>*& p)
{
	Node<Type>* current, *prevCurrent, *temp;
	if (p == NULL)
		cout << "The node to be deleted is NULL!" << endl;
	else if (p->llink == NULL && p->rlink == NULL) //p points to a leaf
	{
		temp = p;
		p = NULL;
		delete temp;
	}
	else if (p->llink == NULL) //p points to a node with only a right child  
	{
		temp = p;
		p = temp->rlink;
		delete temp;
	}
	else if (p->rlink == NULL) //p points to a node with only a left child 
	{
		temp = p;
		p = temp->llink;
		delete temp;
	}
	else//p points to a node with two children
	{
		current = p->llink;
		prevCurrent = NULL;
		while (current->rlink != NULL)
		{
			prevCurrent = current;
			current = current->rlink;
		}
		p->info = current->info;
		if (prevCurrent == NULL)   //current did not move, current = p->llink, adjust p
			p->llink = current->llink;
		else
			prevCurrent->rlink = current->llink;
		delete current;
	}
}

template<class Type>
void BinarySearchTree<Type>::deleteNode(const Type& x)
{
	Node<Type>* current;
	Node<Type>* prevCurrent;
	bool found = false;
	if (this->root == NULL)
		cout << "Cannot delete from an empty tree!" << endl;
	else
	{
		current = this->root;
		prevCurrent = this->root;
		while (current != NULL && !found)
		{
			if (current->info == x)
				found = true;
			else
			{
				prevCurrent = current;
				if (current->info > x)
					current = current->llink;
				else
					current = current->rlink;
			}
		}
		if (current == NULL)
			cout << "The item is not in the tree!" << endl;
		else if (found)
		{
			if (current == this->root)
				deleteFromTree(this->root);
			else
				if (prevCurrent->info > x)
					deleteFromTree(prevCurrent->llink);
				else
					deleteFromTree(prevCurrent->rlink);
		}
	}
}

template<class Type>
bool BinarySearchTree<Type>::search(const Type& x)
{
    Node<Type>* current;
    bool found = false;
    if(this->root == NULL)
        cout << "Cannot search in an empty tree" << endl;
    else{
        current = this->root;
        while(current != NULL && !found){
            if(current->info == x){
                found = true;
            }
            else{
                if(current->info > x)
                    current = current->llink;
                else
                    current = current->rlink;
            }
        }
    }
    return found;
}

template<class Type>
void BinarySearchTree<Type>::inorderTraversal()
{
    return inorder(root);
}

template<class Type>
void BinarySearchTree<Type>::preorderTraversal()
{
    return preorder(root);
}

template<class Type>
void BinarySearchTree<Type>::postorderTraversal()
{
    return postorder(root);
}

template<class Type>
void BinarySearchTree<Type>::inorder(Node<Type>* x)
{
    if(p != NULL){
        inorder(p->llink);
        cout << p->info << " ";
        inorder(p->rlink);
    }
}

template<class Type>
void BinarySearchTree<Type>::preorder(Node<Type>* x)
{
    if(p != NULL){
        cout << p->info << " ";
        preorder(p->llink);
        preorder(p->rlink);
    }
}

template<class Type>
void BinarySearchTree<Type>::postorder(Node<Type>* x)
{
    if(p != NULL){
        postorder(p->llink);
        postorder(p->rlink);
        cout << p->info << " ";
    }
}