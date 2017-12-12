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
 * Destructor
 *******************************************************************/
avltree::~avltree() { //recursive
    delete root;
}

/********************************************************************
 * Search
 *******************************************************************/
bool avltree::search(const int value) const {
    if (root == nullptr)
        return false;
    return root->search(value);
}

bool avltree::node::search(const int value) const {
    if (value == k) return true;
    if (value < k && left != nullptr) return l->search(value);
    if (value > k && right != nullptr) return r->search(value);
    return false;
}

/********************************************************************
 * Insert
 *******************************************************************/
bool avltree::insert(const int key) {
    if (root == nullptr)
        root = new node(key);

    else {
        node *n = root;
        node *parent;

        while (true) {
            if (n->k == key)
                return false;

            parent = n;

            bool toLeft = n->k > key;

            if (toLeft)
                n = n->l;
            else
                n = n->r;

            if (n == nullptr) {
                if (toLeft) {
                    parent->l = new node(key, parent);
                }
                else {
                    parent->r = new node(key, parent);
                }

                rebalance(parent);
                break;
            }
        }
    }

    return true;
}

/********************************************************************
 * Remove
 *******************************************************************/

avltree::node *findSymSucc(avltree::node *n) {
    if (n->r == nullptr)
        return nullptr;
    auto result = n->r;
    while (result->l != nullptr) {
        result = result->l;
    }
    return result;
}

void avltree::remove(const int key) {
    if (root != nullptr) {
        if (root->k == key) {
            auto toDelete = root;
            if (root->l == nullptr && root->r == nullptr) {
                root = nullptr;
            } else if (root->l == nullptr) {
                root = root->r;
            } else if (root->r == nullptr)
                root = root->l;
            else {
                auto symSucc = findSymSucc(root);
                auto toDeleteNode = symSucc;
                root->r = root->r->remove(symSucc->k);
                toDeleteNode->l = nullptr;
                toDeleteNode->r = nullptr;
                root = new node(symSucc->k, root->l, root->r);
                delete toDeleteNode;
            }
            toDelete->l = nullptr;
            toDelete->r = nullptr;
            delete toDelete;
        } else
            root->remove(key);
    }
}

avltree::node *avltree::node::remove(const int key) {

    if (key < k) {
        if (l != nullptr) {
            auto toDelete = l;
            l = l->remove(key);
            if (toDelete->k == key) {
                toDelete->l = nullptr;
                toDelete->r = nullptr;
                delete toDelete;
            }
        }
        return this;
    }

    if (key > k) {
        if (r != nullptr) {
            auto toDelete = r;
            r = r->remove(key);
            if (toDelete->k == key) {
                toDelete->l = nullptr;
                toDelete->r = nullptr;
                delete toDelete;
            }
        }
        return this;
    }

    if (k == key) {
        if (l == nullptr && r == nullptr)
            return nullptr;
        if (l == nullptr)
            return r;
        if (r == nullptr)
            return l;
        auto symSucc = findSymSucc(this);
        return new node(symSucc->k, l, r->remove(symSucc->k));
    }
    // code should not be reached, just to make the compiler happy
    return nullptr;
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
            = [&](std::ostream &, const int value, const avltree::node *n, const string l) {

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

int avltree::height(avltree::node *n) {
    if (n == nullptr)
        return -1;
    return 1 + std::max(height(n->l), height(n->r));
}

void avltree::calcBalance(avltree::node *n) {
    n->balance = height(n->r) - height(n->l);
}

void avltree::rebalance(avltree::node *n) {
    calcBalance(n);
}

void avltree::printBalance() {
    printBalance(root);
    std::cout << std::endl;
}

void avltree::printBalance(avltree::node *n) {
    if (n != nullptr) {
        rebalance(n);
        printBalance(n->l);
        std::cout << n->balance << " ";
        printBalance(n->r);
    }
}