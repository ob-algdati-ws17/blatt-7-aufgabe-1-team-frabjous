#include "testTree.h"
//#include <memory>

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

TEST(TreeTest, TreeTest_InsertTen) {
    avltree avl;

    for (int i = 1; i <= 10; ++i)
        EXPECT_FALSE(avl.search(i));

    for (int i = 1; i <= 10; ++i)
        avl.insert(i);
    for (int i = 1; i <= 10; ++i)
        EXPECT_TRUE(avl.search(i));
}

// remove
TEST(TreeTest, TreeTest_RemoveFromEmptyTree) {
    avltree avl;
    const int i = 117;
    EXPECT_FALSE(avl.search(i));
    avl.remove(i);
    EXPECT_FALSE(avl.search(i));
}

TEST(TreeTest, TreeTest_RemoveOne) {
    avltree avl;
    const int i = 117;
    EXPECT_FALSE(avl.search(i));
    avl.insert(i);
    EXPECT_TRUE(avl.search(i));
    avl.remove(i);
    EXPECT_FALSE(avl.search(i));
}

TEST(TreeTest, TreeTest_RemoveThree) {
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
    avl.remove(k);
    EXPECT_FALSE(avl.search(k));
    avl.remove(j);
    EXPECT_FALSE(avl.search(j));
    avl.remove(i);
    EXPECT_FALSE(avl.search(i));
    EXPECT_FALSE(avl.search(j));
    EXPECT_FALSE(avl.search(k));
}

TEST(TreeTest, TreeTest_RemoveTen) {
    avltree avl;

    for (int i = 1; i <= 10; ++i)
        EXPECT_FALSE(avl.search(i));

    for (int i = 1; i <= 10; ++i)
        avl.insert(i);
    for (int i = 1; i <= 10; ++i)
        EXPECT_TRUE(avl.search(i));

    for (int i = 1; i <= 10; ++i)
        avl.remove(i);
    for (int i = 1; i <= 10; ++i)
        EXPECT_FALSE(avl.search(i));
}