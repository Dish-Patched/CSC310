#include "bst.cpp"

int main()
{
    BinarySearchTree<int> bst;
    bst.insertNode(10);
	bst.insertNode(5);
	bst.insertNode(2);
	bst.insertNode(3);
	bst.insertNode(7);
	bst.insertNode(15); 

    bst.inorderTraversal();

    return 0;
}