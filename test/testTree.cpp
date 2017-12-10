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