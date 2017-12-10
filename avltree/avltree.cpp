#include "avltree.h"
#include <functional>

/********************************************************************
 * operator<<
 *******************************************************************/
//unchanged from Blatt 6
std::ostream &operator<<(std::ostream &os, const avltree &tree) {
    function<void(std::ostream &, const int, const avltree::node *, const string)> printToOs
            = [&](std::ostream &os, const int value, const avltree::node *n, const string l) {

                static int nullcount = 0;

                if (n == nullptr) {
                    os << "    null" << nullcount << "[shape=point];" << endl;
                    os << "    " << value << " -> null" << nullcount
                       << " [label=\"" << l << "\"];" << endl;
                    nullcount++;
                } else {
                    os << "    " << value << " -> " << n->key
                       << " [label=\"" << l << "\"];" << endl;

                    printToOs(os, n->key, n->l, "l");
                    printToOs(os, n->key, n->r, "r");
                }
            };
    os << "digraph tree {" << endl;
    if (tree.root == nullptr) {
        os << "    null " << "[shape=point];" << endl;
    } else {
        printToOs(os, tree.root->key, tree.root->l, "l");
        printToOs(os, tree.root->key, tree.root->r, "r");
    }
    os << "}" << endl;
    return os;
}