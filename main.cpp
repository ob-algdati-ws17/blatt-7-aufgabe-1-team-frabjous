#include <iostream>
#include "avltree.h"

using namespace std;

int main() {

    avltree tree;
    cout << tree << endl;

    tree.insert(117);
    cout << tree << endl;

    return 0;
}
