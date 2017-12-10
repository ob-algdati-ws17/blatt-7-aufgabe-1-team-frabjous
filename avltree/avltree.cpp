#include "avltree.h"
#include <functional>

using namespace ::std;

/********************************************************************
 * Node Destructor
 *******************************************************************/
avltree::node::~node() { //recursive
    delete l;
    delete r;
}

/********************************************************************
 * Insert
 *******************************************************************/
void avltree::insert(const int key) {
    if (root == nullptr) { //empty tree
        root = new node(key);
    }
}

/********************************************************************
 * Traversal
 *******************************************************************/
//unchanged from Blatt 6

vector<int> *avltree::preorder() const {
    if (root == nullptr)
        return nullptr;
    return root->preorder();
}

vector<int> *avltree::node::preorder() const {
    auto vec = new vector<int>();
    // Wurzel in vec
    vec->push_back(k);
    // linken Nachfolger in vec
    if (l != nullptr) {
        auto left_vec = l->preorder();
        vec->insert(vec->end(), left_vec->begin(), left_vec->end());
    }
    // rechten Nachfolger in vec
    if (r != nullptr) {
        auto right_vec = r->preorder();
        vec->insert(vec->end(), right_vec->begin(), right_vec->end());
    }
    return vec;
}

vector<int> *avltree::inorder() const {
    if (root == nullptr)
        return nullptr;
    return root->inorder();
}

vector<int> *avltree::node::inorder() const {
    auto vec = new vector<int>();
    // linken Nachfolger in vec
    if (l != nullptr) {
        auto left_vec = l->inorder();
        vec->insert(vec->end(), left_vec->begin(), left_vec->end());
    }
    // Wurzel in vec
    vec->push_back(k);
    // rechten Nachfolger in vec
    if (r != nullptr) {
        auto right_vec = r->inorder();
        vec->insert(vec->end(), right_vec->begin(), right_vec->end());
    }
    return vec;
}

vector<int> *avltree::postorder() const {
    if (root == nullptr)
        return nullptr;
    return root->postorder();
}

vector<int> *avltree::node::postorder() const {
    auto vec = new vector<int>();
    // linken Nachfolger in vec
    if (l != nullptr) {
        auto left_vec = l->postorder();
        vec->insert(vec->end(), left_vec->begin(), left_vec->end());
    }
    // rechten Nachfolger in vec
    if (r != nullptr) {
        auto right_vec = r->postorder();
        vec->insert(vec->end(), right_vec->begin(), right_vec->end());
    }
    // Wurzel in vec
    vec->push_back(k);
    return vec;
}

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
                    os << "    " << value << " -> " << n->k
                       << " [label=\"" << l << "\"];" << endl;

                    printToOs(os, n->k, n->l, "l");
                    printToOs(os, n->k, n->r, "r");
                }
            };
    os << "digraph tree {" << endl;
    if (tree.root == nullptr) {
        os << "    null " << "[shape=point];" << endl;
    } else {
        printToOs(os, tree.root->k, tree.root->l, "l");
        printToOs(os, tree.root->k, tree.root->r, "r");
    }
    os << "}" << endl;
    return os;
}