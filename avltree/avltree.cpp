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
    if (root == nullptr) //leerer Baum
        root = new node(key);
    else if (!search(key)) //ist noch nicht im Baum
        insertAt(key, root, nullptr);
    // else: Duplikat, nichts zu tun
}

void avltree::insertAt(const int key, avltree::node *n, avltree::node *p) {

    while (true) {
        p = n; //iterating
        if (key < n->k) { //nach links
            if (n->l == nullptr) { //platz für eine neue node
                n->l = new node(key);
                n = n->l;
                n->p = p;
                break; //raus aus dem loop
            }
            n = n->l; //sonst iterieren
        } else if (key > n->k) { //nach rechts
            if (n->r == nullptr) {
                n->r = new node(key);
                n = n->r;
                n->p = p;
                break;
            }
            n = n->r;
        }
    }

    if (p->bal != 0) { //vorher unausgeglichen (fall 1 & 2)
        p->bal = 0; //jetzt stimmts
    } else { //(fall 3)
        if (n == p->r) { //rechts was dazugekommen
            p->bal = 1;
        } else if (n == p->l) { //links was dazugekommen
            p->bal = -1;
        }
        upin(p);
    }

}

void avltree::upin(avltree::node *n) {
    if (n == root) //Wurzel erreicht, Rekursionsende
        return;

    if (n == n->p->l) { //Baum ist linksseitig gewachsen
        n->p->bal--; //Balance updaten
        if (n->p->bal == 0) {
            return; //fertig
        } else if (n->p->bal == -1) { //weiteriterieren
            upin(n->p);
        } else if (n->p->bal < -1) { //Neu balancieren und fertig
            if (n->bal == -1) {
                rotateRight(n->p);
                return;
            } else if (n->bal == 1) {
                rotateLeftRight(n->p);
                return;
            }
        }
    } else if (n == n->p->r) { //rechtsseitig gewachsen
        n->p->bal++;
        if (n->p->bal == 0) {
            return;
        } else if (n->p->bal == 1) {
            upin(n->p);
        } else if (n->p->bal > 1) {
            if (n->bal == 1) {
                rotateLeft(n->p);
                return;
            } else if (n->bal == -1) {
                rotateRightLeft(n->p);
                return;
            }
        }
    }
}

void avltree::remove(const int key) {
    if (root == nullptr) //leerer Baum
        return;
    else if (search(key)) //ist im Baum
        removeAt(key, root);
    // else: nicht im Baum, nichts zu tun
}

void avltree::removeAt(const int key, avltree::node *n) {
    while (n != nullptr) { //Schlüssel finden
        if (n->k == key)
            break;
        else if (key < n->k)
            n = n->l;
        else if (key > n->k)
            n = n->r;
    }

    if (n != nullptr) {
        if (n->l == nullptr && n->r == nullptr) { //Beide Nachfolger Blätter (Fall 1)

            if (n == root) { //root entfernen
                root = nullptr;
                return;
            }

            if (n == n->p->l) { //links entfernen
                n->p->bal++; //Balance anpassen (links ist was weggekommen, also wird Balance größer)
                if (n->p->bal == 1) { //Fall 1.1
                    n->p->l = nullptr;
                    return;
                }
                if (n->p->bal == 0) { //Fall 1.2
                    n->p->l = nullptr;
                    upout(n->p);
                    return;
                }
                if (n->p->bal == 2) { //Fall 1.3
                    n->p->bal = 1;
                    upout(n);
                    n->p->l = nullptr;
                    return;
                }
            } else if (n == n->p->r) { //rechts entfernen
                n->p->bal--;
                if (n->p->bal == -1) {
                    n->p->r = nullptr;
                    return;
                }
                if (n->p->bal == 0) {
                    n->p->r = nullptr;
                    upout(n->p);
                    return;
                }
                if (n->p->bal == -2) {
                    n->p->bal = -1;
                    upout(n);
                    n->p->r = nullptr;
                    return;
                }
            }

        } else if (n->l != nullptr && n->r == nullptr) { //Fall 2: Blatt rechts
            if (n == root) { //root entfernen
                root = n->l;
                root->p = nullptr;
                return;
            } else if (n == n->p->l) { //linker Nachfolger
                n->p->l = n->l; //n macht Platz für den eigenen Nachfolger
                n->p->l->p = n->p; //richtig mit Vorgänger verpointern
                upout(n->p->l);
            } else { //rechter Nachfolger
                n->p->r = n->l;
                n->p->r->p = n->p;
                upout(n->p->r);
            }
        } else if (n->r != nullptr && n->l == nullptr) { //Fall 2: Blatt links
            if (n == root) {
                root = n->r;
                root->p = nullptr;
                return;
            } else if (n == n->p->r) {
                n->p->r = n->r;
                n->p->r->p = n->p;
                upout(n->p->r);
            } else {
                n->p->l = n->r;
                n->p->l->p = n->p;
                upout(n->p->l);
            }
        }
    } else if (n->l != nullptr && n->r != nullptr) { //Fall 3: Beide Blätter
        std::cout << "RM need symbolic successor here" << std::endl;
    }
}

void avltree::upout(avltree::node *n) {
    if (n == root) //Ende der Rekursion
        return;

    if (n == n->p->l) { //linker Nachfolger
        if (n->p->bal == -1) { //Fall 1.1
            n->p->bal++;
            upout(n->p);
        } else if (n->p->bal == 0) { //Fall 1.2
            n->p->bal++;
            return;
        } else if (n->p->bal == 1) { //Fall 1.3
            if (n->p->r->bal == 0) { //Fall 1.3.1
                rotateLeft(n->p);
                n->p->bal = 1;
                n->p->p->bal = -1;
                return;
            } else if (n->p->r->bal == 1) { //Fall 1.3.2
                rotateLeft(n->p);
                upout(n->p->p);
                return;
            } else if (n->p->r->bal == -1) { //Fall 1.3.3
                rotateRightLeft(n->p);
                upout(n->p->p);
                return;
            }
        }
    } else if (n == n->p->r) { //rechter Nachfolger
        if (n->p->bal == 1) {
            n->p->bal--;
            upout(n->p);
        } else if (n->p->bal == 0) {
            n->p->bal--;
            return;
        } else if (n->p->bal == -1) {
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

void avltree::rotateLeft(avltree::node *a) {
    //std::cout << "ROTATE LEFT @ " << a->k << " & " << a->r->k << std::endl;
    avltree::node *b = a->r;

    if (a == root) {
        root = b;
        root->p = nullptr;
    } else {
        if (a->p->r == a) { //RIGHT
            a->p->r = b;
            b->p = a->p;
        } else if (a->p->l == a) { //LEFT
            a->p->l = b;
            b->p = a->p;
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

void avltree::rotateRight(avltree::node *a) {
    //std::cout << "ROTATE RIGHT @ " << a->k << " & " << a->l->k << std::endl;
    avltree::node *b = a->l;

    if (a == root) {
        root = b;
        root->p = nullptr;
    } else {
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

void avltree::rotateLeftRight(avltree::node *a) {
    rotateLeft(a->l);
    rotateRight(a);
}

void avltree::rotateRightLeft(avltree::node *a) {
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