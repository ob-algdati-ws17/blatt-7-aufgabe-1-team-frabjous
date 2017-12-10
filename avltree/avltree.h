#ifndef MAIN_TREE_H
#define MAIN_TREE_H

#include <iostream>
#include <vector>

using namespace std;

class avltree {

private:

    struct node {
        const int key;
        node *parent = nullptr;
        node *l = nullptr;
        node *r = nullptr;
        //node(const int);
        //node(const int, Node *, Node *);
        /*~Node();*/
        vector<int> *preorder() const;  // (Hauptreihenfolge)
        vector<int> *inorder() const;   // (Symmetrische Reihenfolge)
        vector<int> *postorder() const; // (Nebenreihenfolge)
    };

    node *root = nullptr;

public:

    //~Tree();

    //bool search(const int) const;

    //void insert(const int);

    //void remove(const int);

    vector<int> *preorder() const;  // (Hauptreihenfolge)
    vector<int> *inorder() const;   // (Symmetrische Reihenfolge)
    vector<int> *postorder() const; // (Nebenreihenfolge)*/

    friend ostream &operator<<(ostream &, const avltree &);

};

#endif
