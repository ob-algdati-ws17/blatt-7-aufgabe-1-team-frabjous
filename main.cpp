#include <iostream>
#include "avltree.h"

using namespace std;

int main() {

    avltree tree;
    cout << tree << endl;

    tree.insert(117);
    cout << tree << endl;

    tree.insert(256);
    cout << tree << endl;

    tree.insert(99);
    cout << tree << endl;

    return 0;
}
