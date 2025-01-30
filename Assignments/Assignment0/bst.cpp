#include "bst.h"
#include "customErrorClass.h"

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
                throw MyException("Node already exists");
                return;
            }
            else{
                if(current->info > x)
                    current = current->llink;
                else    
                    current = current->rlink;
            }
        }
        if(prevCurrent->info > x)
            prevCurrent->llink = newNode;
        else
            prevCurrent->rlink = newNode;
    }
}


template<class Type>
void BinarySearchTree<Type>::deleteFromTree(Node<Type>*& p)
{
	Node<Type>* current, *prevCurrent, *temp;
	if (p == NULL)
		throw MyException("The node to be deleted is NULL!");
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
		if (prevCurrent == NULL)   
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
		throw MyException("Cannot delete from an empty tree!");
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
			throw MyException("The item is not in the tree!");
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
        throw MyException("Cannot search in an empty tree");
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
void BinarySearchTree<Type>::inorder(Node<Type>* p)
{
    if(p != NULL){
        inorder(p->llink);
        cout << p->info << " ";
        inorder(p->rlink);
    }
}

template<class Type>
void BinarySearchTree<Type>::preorder(Node<Type>* p)
{
    if(p != NULL){
        cout << p->info << " ";
        preorder(p->llink);
        preorder(p->rlink);
    }
}

template<class Type>
void BinarySearchTree<Type>::postorder(Node<Type>* p)
{
    if(p != NULL){
        postorder(p->llink);
        postorder(p->rlink);
        cout << p->info << " ";
    }
}

template<class Type>
Type BinarySearchTree<Type>::sum(Node<Type>* p)
{
    if(p == NULL)
        return 0;
    else{
        return p->info + sum(p->llink) + sum(p->rlink);
    }
}

template<class Type>
void BinarySearchTree<Type>::treeState(){
    if(root == NULL)
        throw MyException("The tree is empty");
    else{
        if(sum(root->llink) == sum(root->rlink))
            cout << "Balanced Tree";
        else if(sum(root->llink) > sum(root->rlink))
            cout << "Left Heavy Tree";
        else if(sum(root->llink) < sum(root->rlink))
            cout << "Right Heavy Tree";
    }
}

template<class Type>
Type BinarySearchTree<Type>::max(Type x, Type y)
{
    if(x > y)
        return x;
    else
        return y;
}

template<class Type>
int BinarySearchTree<Type>::height(Node<Type>* p)
{
    if(p == NULL)
        return 0;
    else{
        return 1 + max(height(p->llink), height(p->rlink));
    }
}

template<class Type>
int BinarySearchTree<Type>::treeHeight()
{
    return height(root);
}

template<class Type>
void BinarySearchTree<Type>::destroy(Node<Type>*& p)
{
	if (p != NULL)
	{
		destroy(p->llink);
		destroy(p->rlink);
		delete p;
		p = NULL;
	}
}

template<class Type>
BinarySearchTree<Type>::~BinarySearchTree()
{
    destroy(root);
}