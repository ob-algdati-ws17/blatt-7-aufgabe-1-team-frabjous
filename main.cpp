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

    /*tree.insert(2);
    tree.insert(1);
    tree.insert(3);
    tree.insert(4);

    cout << endl << endl << endl;

    tree.insert(5);tree.insert(7);tree.insert(6);tree.insert(8);tree.insert(9);

    cout << tree << endl;

    tree.printBalance();*/

    for (int i = 1; i <= 3; ++i)
        tree.insert(i);
    cout << tree << endl;

    return 0;
}
