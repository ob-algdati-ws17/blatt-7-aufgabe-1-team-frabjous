#ifndef MAIN_TREE_H
#define MAIN_TREE_H

#include <iostream>
#include <vector>

using namespace std;

class avltree {

private:

    struct node {
        const int k; //key
        node *parent = nullptr;
        node *l = nullptr; //left
        node *r = nullptr; //right
        node(const int ey) : k(ey) {};
        node(const int ey, node *eft, node *ight) : k(ey), l(eft), r(ight) {};
        ~node();
        vector<int> *preorder() const;  // (Hauptreihenfolge)
        vector<int> *inorder() const;   // (Symmetrische Reihenfolge)
        vector<int> *postorder() const; // (Nebenreihenfolge)
    };

    node *root = nullptr;

public:

    //~Tree();

    //bool search(const int) const;

    void insert(const int);

    //void remove(const int);

    vector<int> *preorder() const;  // (Hauptreihenfolge)
    vector<int> *inorder() const;   // (Symmetrische Reihenfolge)
    vector<int> *postorder() const; // (Nebenreihenfolge)*/

    friend ostream &operator<<(ostream &, const avltree &);

};

#endif
