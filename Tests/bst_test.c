#include "BSTree.h"
#include "bst_test.h"

TEST_FUN_IMPL(BSTTest, CreateAndInsert) {
    BST* tree = BST_create();
    TEST_ASSERT(tree != NULL);

    bool insertResult = BST_insert(tree, 5);
    TEST_ASSERT(insertResult);

    BSTNode* found = BST_find(tree, 5);
    TEST_ASSERT(found != NULL);
    TEST_ASSERT_EQ(found->data, 5, "%d");

    BST_free(tree);
} END_FUN

TEST_FUN_IMPL(BSTTest, FindNonExistent) {
    BST* tree = BST_create();
    BST_insert(tree, 5);

    BSTNode* found = BST_find(tree, 10);
    TEST_ASSERT(found == NULL);

    BST_free(tree);
} END_FUN

INIT_TEST_SUITE(BSTTest)
BIND_TEST(BSTTest, CreateAndInsert)
BIND_TEST(BSTTest, FindNonExistent)
END_INIT_TEST_SUITE(BSTTest)
