#include "bst.cpp"

int main()
{
	try{
		BinarySearchTree<int> bst;
		bst.insertNode(10);
		bst.insertNode(5);
		bst.insertNode(2);
		bst.insertNode(3);
		bst.insertNode(7);
		bst.insertNode(15); 

		bst.inorderTraversal();
		cout << endl;
		bst.preorderTraversal();
		cout << endl;
		bst.postorderTraversal();
		cout << endl;

		bst.deleteNode(2);
		bst.inorderTraversal();
		cout << endl;

		cout << bst.search(7) << endl;

		bst.treeState();
		cout << endl;

		cout << bst.treeHeight() << endl;
	}
	catch( MyException &e){
		cerr<<e.what()<<endl;
	}
	

    return 0;
}