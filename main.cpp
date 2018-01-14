#include <iostream>
#include "avltree.h"

using namespace std;

int main() {

    avltree tree;

    for (int i = 1; i <= 99; ++i)
        tree.insert(i);
    cout << tree << endl;

    tree.remove(10);

    return 0;
}
