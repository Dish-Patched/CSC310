#include "avl.h"

int main()
{
    try{
        AVLTree avl;

        avl.insert(10);
        avl.insert(20);
        avl.insert(30);
        avl.insert(40);
        avl.insert(50);
        avl.insert(25);

        avl.print();

        cout << "After deletion: " << endl;

        avl.remove(30);

        avl.print();
    }
    catch( MyException &e){
		cerr<<e.what()<<endl;
	}

    return 0;
}