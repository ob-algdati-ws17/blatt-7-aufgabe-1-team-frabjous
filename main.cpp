#include <iostream>
#include "avltree.h"

using namespace std;

int main() {

    avltree tree;
    //cout << tree << endl;

    /*tree.insert(117);
    cout << tree << endl;
    tree.printBalance();

    tree.insert(256);
    cout << tree << endl;
    tree.printBalance();

    tree.insert(99);
    cout << tree << endl;
    tree.printBalance();*/

    tree.insert(2);
    tree.insert(1);
    tree.insert(3);
    tree.insert(4);
    tree.insert(5);

    cout << tree << endl;

    tree.printBalance();

    return 0;
}
