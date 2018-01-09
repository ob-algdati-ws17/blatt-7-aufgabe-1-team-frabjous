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
    //std::cout << "INS key " << key << std::endl;
    if (root == nullptr) //empty tree
        root = new node(key);
    else if (!search(key)) //not already in tree
            insertAt(key, root, nullptr);
    // else it's a duplicate
}

void avltree::insertAt(const int key, avltree::node *n, avltree::node *p) {

    while(true){
        p = n; //iterating
        if(key < n->k){
            if(n->l == nullptr){
                n->l = new node(key);
                n = n->l;
                n->p = p;
                break;
            }
            n = n->l;
        }
        else if(key>n->k){
            if(n->r == nullptr){
                n->r = new node(key);
                n = n->r;
                n->p = p;
                break;
            }
            n = n->r;
        }
    }

    if(p->bal!=0) { //height unchanged
        p->bal=0;
    }
    else {
        if(p->r == n){
            p->bal = 1;
        }
        if(p->l == n){
            p->bal = -1;
        }
        upin(p);
    }

}

void avltree::upin(avltree::node *n) {
    if(n == root) //top of tree, end of recursion
        return;

    if(n->p->r == n){ //right
        n->p->bal++;
        if(n->p->bal == 0){
            return;
        }
        else if(n->p->bal == 1){
            upin(n->p);
        }
        else if(n->p->bal > 1){
            if(n->bal == 1) {
                rotateLeft(n->p);
                return;
            }
            else if(n->bal == -1){
                rotateRightLeft(n->p);
                return;
            }
        }
    }
    else if(n->p->l == n){ //left
        n->p->bal--;
        if(n->p->bal == 0){
            return;
        }
        else if(n->p->bal == -1){
            upin(n->p);
        }
        else if(n->p->bal < -1){
            if(n->bal == -1) {
                rotateRight(n->p);
                return;
            }
            else if(n->bal == 1){
                rotateLeftRight(n->p);
                return;
            }
        }
    }
}

void avltree::remove(const int key) {
    if (root == nullptr) //empty tree
        return;
    else if (search(key)) //already in tree
        std::cout << "RM key " << key << std::endl; //insertAt(key, root, nullptr);
    // else it's not even in the tree
}

void avltree::upout(avltree::node *n){
    if(n == root) //top of tree, end of recursion
        return;

    if(n->p->l == n){ //left
        if(n->p->bal == -1) {
            n->p->bal++;
            upout(n->p);
        }
        else if(n->p->bal == 0){
            n->p->bal++;
            return;
        }
        else if(n->p->bal == 1){
            if(n->p->r->bal == 0){
                rotateLeft(n->p);
                n->p->bal=1;
                n->p->p->bal=-1;
                return;
            }
            else if(n->p->r->bal == 1){
                rotateLeft(n->p);
                upout(n->p->p);
                return;
            }
            else if(n->p->r->bal == -1){
                rotateRightLeft(n->p);
                upout(n->p->p);
                return;
            }
        }
    }
    else if(n->p->r == n){ //right
        if(n->p->bal == 1) {
            n->p->bal--;
            upout(n->p);
        }
        else if(n->p->bal == 0){
            n->p->bal--;
            return;
        }
        else if(n->p->bal == -1) {
            if (n->p->l->bal == 0) {
                rotateRight(n->p);
                n->p->bal = -1;
                n->p->p->bal = 1;
                return;
            } else if (n->p->l->bal == -1) {
                rotateRight(n->p);
                upout(n->p->p);
                return;
            } else if (n->p->l->bal == 1) {
                rotateLeftRight(n->p);
                upout(n->p->p);
                return;
            }
        }
    }
}

void avltree::rotateLeft(avltree::node* a) {
    //std::cout << "ROTATE LEFT @ " << a->k << " & " << a->r->k << std::endl;
    avltree::node *b = a->r;

    if (a == root){
        root = b;
        root->p = nullptr;
    }

    else {
        if (a->p->r == a) { //RIGHT
            a->p->r=b;
            b->p=a->p;
        } else if (a->p->l == a) { //LEFT
            a->p->l = b;
            b->p=a->p;
        }
    }

    a->r = b->l;

    if (a->r != nullptr)
        a->r->p = a;

    b->l = a;
    a->p = b;
    a->bal = 0;
    b->bal = 0;
}

void avltree::rotateRight(avltree::node* a) {
    //std::cout << "ROTATE RIGHT @ " << a->k << " & " << a->l->k << std::endl;
    avltree::node *b = a->l;

    if(a == root){
        root = b;
        root->p = nullptr;
    }
    else {
        if (a->p->r == a) { //right
            a->p->r = b;
            b->p = a->p;
        } else if (a->p->l == a) { //left
            a->p->l = b;
            b->p = a->p;
        }
    }

    a->l = b->r;

    if (a->l != nullptr)
        a->l->p = a;

    b->r = a;
    a->p = b;
    b->bal = 0;
    a->bal = 0;
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
 * operator<<
 *******************************************************************/
std::ostream &operator<<(std::ostream &os, const avltree &tree) {
    function<void(std::ostream &, const int, const int, const avltree::node *, const string)> printToOs
            = [&](std::ostream &, const int value, const int bal, const avltree::node *n, const string l) {

                static int nullcount = 0;

                os << "    " << value << " [label=\"" << value << " b" << bal << "\"];" << endl;

                if (n == nullptr) {
                    os << "    null" << nullcount << "[shape=point];" << endl;
                    os << "    " << value << " -> null" << nullcount
                       << " [label=\"" << l << "\"];" << endl;
                    nullcount++;
                } else {
                    os << "    " << value << " -> " << n->k
                       << " [label=\"" << l << "\"];" << endl;


                    printToOs(os, n->k, n->bal, n->l, "l");
                    printToOs(os, n->k, n->bal, n->r, "r");
                }
            };
    os << "digraph tree {" << endl;
    if (tree.root == nullptr) {
        os << "    null " << "[shape=point];" << endl;
    } else {
        printToOs(os, tree.root->k, tree.root->bal, tree.root->l, "l");
        printToOs(os, tree.root->k, tree.root->bal, tree.root->r, "r");
    }
    os << "}" << endl;
    return os;
}

int avltree::height(avltree::node *n) {
    if (n == nullptr)
        return -1;
    return 1 + std::max(height(n->l), height(n->r));
}