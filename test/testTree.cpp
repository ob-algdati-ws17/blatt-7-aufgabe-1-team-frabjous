#include "testTree.h"
#include <memory>

using namespace std;

//trivial / testing travis integration

TEST(TreeTest, TreeTest_Trivial) {
    avltree avl;
    EXPECT_EQ(1, 1);
}


// insert

TEST(TreeTest, TreeTest_InsertIntoEmptyTree) {
    avltree avl;
    const int i = 117;
    EXPECT_FALSE(avl.search(i));
    avl.insert(i);
    EXPECT_TRUE(avl.search(i));
}

TEST(TreeTest, TreeTest_InsertThree) {
    avltree avl;
    const int i = 117;
    const int j = 256;
    const int k = 99;
    EXPECT_FALSE(avl.search(i));
    EXPECT_FALSE(avl.search(j));
    EXPECT_FALSE(avl.search(k));
    avl.insert(i);
    EXPECT_TRUE(avl.search(i));
    avl.insert(j);
    EXPECT_TRUE(avl.search(j));
    avl.insert(k);
    EXPECT_TRUE(avl.search(k));
}