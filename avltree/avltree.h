#ifndef MAIN_TREE_H
#define MAIN_TREE_H

#include <iostream>
#include <vector>

using namespace std;

class avltree {

private:

    struct node {
        const int k; //key
        node *p = nullptr; //parent
        node *l = nullptr; //left
        node *r = nullptr; //right
        int bal = 0; //balance

        node(const int ey) : k(ey) {};
        node(const int ey, node *arent) : k(ey), p(arent) {};
        node(const int ey, node *eft, node *ight) : k(ey), l(eft), r(ight) {};
        node(const int ey, node *eft, node *ight, node *arent) : k(ey), l(eft), r(ight), p(arent) {};
        ~node();

        bool search(const int) const;
    };

    node *root = nullptr;

    void insertAt(const int, node*, node*);
    void upin(node*);

    void removeAt(const int, node*);
    void upout(node*);

    void rotateLeft(node*);
    void rotateRight(node*);
    void rotateLeftRight(node*);
    void rotateRightLeft(node*);

    int height(node*);

public:

    ~avltree();

    bool search(const int) const;
    void insert(const int);
    void remove(const int);

    friend node *findSymSucc(node *);
    friend ostream &operator<<(ostream &, const avltree &);

};

#endif
