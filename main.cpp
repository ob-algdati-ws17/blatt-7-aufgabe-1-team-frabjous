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

    for (int i = 1; i <= 10; ++i)
        tree.insert(i);

    cout << tree << endl;

    tree.printBalance();

    return 0;
}
