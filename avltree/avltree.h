#ifndef MAIN_TREE_H
#define MAIN_TREE_H

#include <iostream>
#include <vector>

using namespace std;

class avltree {

private:

    struct node {
        const int k; //key
        node *p = nullptr;
        node *l = nullptr; //left
        node *r = nullptr; //right
        //int height = 1; //new nodes start as leaves
        int bal = 0;

        node(const int ey) : k(ey) {};
        node(const int ey, node *arent) : k(ey), p(arent) {};
        node(const int ey, node *eft, node *ight) : k(ey), l(eft), r(ight) {};
        ~node();

        bool search(const int) const;
        //void insert(const int, node*);
        //node *remove(const int);

        /*vector<int> *preorder() const;  // (Hauptreihenfolge)
        vector<int> *inorder() const;   // (Symmetrische Reihenfolge)
        vector<int> *postorder() const; // (Nebenreihenfolge)*/
    };

    node *root = nullptr;

    void insertAt(const int, node*, node*);
    void upin(node*);

    int height(node*);
    void calcBalance(node*);
    void rebalance(node*);
    void printBalance(node*);

public:

    ~avltree();

    bool search(const int) const;
    void insert(const int);
    //void remove(const int);

    /*vector<int> *preorder() const;  // (Hauptreihenfolge)
    vector<int> *inorder() const;   // (Symmetrische Reihenfolge)
    vector<int> *postorder() const; // (Nebenreihenfolge)*/

    //friend node *findSymSucc(node *);
    friend ostream &operator<<(ostream &, const avltree &);
    void printBalance();

};

#endif
