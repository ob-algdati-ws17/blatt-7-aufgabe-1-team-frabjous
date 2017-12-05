#include "avltree.h"
#include <functional>

/********************************************************************
 * operator<<
 *******************************************************************/
std::ostream &operator<<(std::ostream &os, const avltree &tree) {
    /*function<void(std::ostream &, const int, const avltree::Node *, const string)> printToOs
                                                                                           = [&](std::ostream &os, const int value, const avltree::node *n, const string l) {

                static int nullcount = 0;

                if (n == nullptr) {
                    os << "    null" << nullcount << "[shape=point];" << endl;
                    os << "    " << value << " -> null" << nullcount
                       << " [label=\"" << l << "\"];" << endl;
                    nullcount++;
                } else {
                    os << "    " << value << " -> " << node->key
                       << " [label=\"" << l << "\"];" << endl;

                    printToOs(os, n->key, n->left, "l");
                    printToOs(os, n->key, n->right, "r");
                }
            };
    os << "digraph tree {" << endl;
    if (tree.root == nullptr) {
        os << "    null " << "[shape=point];" << endl;
    } else {
        printToOs(os, tree.root->key, tree.root->left, "l");
        printToOs(os, tree.root->key, tree.root->right, "r");
    }
    os << "}" << endl;
    return os;*/

    os << "i'm printing!" << std::endl;
    return os;
}