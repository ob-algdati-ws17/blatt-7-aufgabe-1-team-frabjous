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
    if (value < k && l != nullptr) return l->search(value);
    if (value > k && r != nullptr) return r->search(value);
    return false;
}

/********************************************************************
 * Insert
 *******************************************************************/
void avltree::insert(const int key) {
    std::cout << "INS key " << key << std::endl;
    if (root == nullptr) { //leerer Baum
        std::cout << "INS empty tree" << std::endl;
        root = new node(key);
    } else {
        /*node *n = root;
        node *parent;

        while (true) {
            if (n->k == key) //keys sind unique
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
        }*/

        if (!search(key)) {
            std::cout << "INS actual insert" << std::endl;
            insertAt(key, root, nullptr);
        } else
            std::cout << "INS key duplicate" << std::endl;
    }
}


void avltree::insertAt(const int key, avltree::node *p, avltree::node *gp) {
    if (p != nullptr) {
        std::cout << "INS key " << key << " @ parent " << p->k << ", Balance " << p->bal << std::endl;
        gp = p;
    }

    if (p == nullptr) { //actual insert
        std::cout << "INS actual insert with parent " << gp->k << std::endl;
        if (key < gp->k) {
            std::cout << "INS left of " << gp->k << std::endl;
            gp->l = new node(key, gp);
            gp->bal -= 1;
            upin(gp->l);
            return;
        } else if (key > gp->k) {
            std::cout << "INS right of " << gp->k << std::endl;
            gp->r = new node(key, gp);
            gp->bal += 1;
            upin(gp->r);
            return;
        } else
            return;
    }

    if (p->bal == 1) { //fall 1
        std::cout << "INS 1" << std::endl;
        insertAt(key, p->l, p);
    } else if (p->bal == -1) { //fall 2
        std::cout << "INS 2" << std::endl;
        insertAt(key, p->r, p);
    } else if (p->bal == 0) { //fall 3
        if (key > p->k) { //fall 3.1
            std::cout << "INS 3.1" << std::endl;
            p->bal += 1;
            insertAt(key, p->r, p);
        } else if (key < p->k) { //fall 3.2
            std::cout << "INS 3.2" << std::endl;
            p->bal -= 1;
            insertAt(key, p->l, p);
        }
    } else {
        std::cout << "INS FUKKEN IMBALANCE" << std::endl;
    }

}

void avltree::upin(avltree::node *n) {
    std::cout << "UPIN, key " << n->k << std::endl;

    if (n->p == nullptr) {
        std::cout << "UPIN: root reached." << std::endl;
        return;
    }

    std::cout << "UPIN balance " << n->bal << " parent balance " << n->p->bal << std::endl;

    if (n->k < n->p->k) { // n linker nachfolger von p
        std::cout << "UPIN: Left" << std::endl;

        if (n->p->bal == 1) {
            std::cout << "UPIN: Left 1.1" << std::endl;
            n->p->bal = 0;
            return;
        }

        if (n->p->bal == 0) {
            std::cout << "UPIN: Left 1.2" << std::endl;
            n->p->bal = -1;
            std::cout << "UPIN: recursive to parent " << n->p->k << std::endl;
            upin(n->p);
            return;
        }

        if (n->p->bal == -1) {
            std::cout << "UPIN: Left 1.3" << std::endl;
            if (n->bal == -1) {
                std::cout << "UPIN: Left 1.3.1" << std::endl;
                rotateRight(n);
                return;
            }
            if (n->bal == 1) {
                std::cout << "UPIN: Left 1.3.2" << std::endl;
                rotateLeftRight(n);
                return;
            }

        }

    } else { //n rechter nachfolger von p
        std::cout << "UPIN: Right" << std::endl;

        if (n->p->bal == -1) {
            std::cout << "UPIN: Right 1.1" << std::endl;
            n->p->bal = 0;
            return;
        }

        if (n->p->bal == 0) {
            std::cout << "UPIN: Right 1.2" << std::endl;
            n->p->bal = 1;
            std::cout << "UPIN: recursive to parent " << n->p->k << std::endl;
            upin(n->p);
            return;
        }

        if (n->p->bal == 1) {
            std::cout << "UPIN: Right 1.3" << std::endl;
            if (n->bal == 1) {
                std::cout << "UPIN: Right 1.3.1" << std::endl;
                rotateLeft(n);
                return;
            }
            if (n->bal == -1) {
                std::cout << "UPIN: Right 1.3.2" << std::endl;
                rotateRightLeft(n);
                return;
            }

        }

    }
}

void avltree::rotateLeft(avltree::node* a) {
    std::cout << "ROTATE LEFT @ " << a->k << " & " << a->r->k << std::endl;
    avltree::node *b = a->r;
    b->p = a->p;
    a->r = b->l;

    if (a->r != nullptr)
        a->r->p = a;

    b->l = a;
    a->p = b;

    if (b->p != nullptr) {
        if (b->p->r == a) {
            b->p->r = b;
        }
        else {
            b->p->l = b;
        }
    }

    calcBalance(a);
    calcBalance(b);
}

void avltree::rotateRight(avltree::node* a) {
    std::cout << "ROTATE RIGHT @ " << a->k << " & " << a->l->k << std::endl;
    avltree::node *b = a->l;
    b->p = a->p;
    a->l = b->r;

    if (a->l != nullptr)
        a->l->p = a;

    b->r = a;
    a->p = b;

    if (b->p != nullptr) {
        if (b->p->r == a) {
            b->p->r = b;
        }
        else {
            b->p->l = b;
        }
    }

    calcBalance(a);
    calcBalance(b);
}

void avltree::rotateLeftRight(avltree::node* a) {
    rotateLeft(a->l);
    rotateRight(a);
}

void avltree::rotateRightLeft(avltree::node* a) {
    rotateRight(a->r);
    rotateLeft(a);
}


/********************************************************************
 * Remove
 *******************************************************************/

/*avltree::node *findSymSucc(avltree::node *n) {
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
}*/


/********************************************************************
 * Traversal
 *******************************************************************/
//unchanged from Blatt 6

/*vector<int> *avltree::preorder() const {
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
}*/

/********************************************************************
 * operator<<
 *******************************************************************/
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
                    os << "    " << value << " [xlabel=\"" << n->bal << "\"];" << endl;

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
    n->bal = height(n->r) - height(n->l);
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
        std::cout << n->bal << " ";
        printBalance(n->r);
    }
}