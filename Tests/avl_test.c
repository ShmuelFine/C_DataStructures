#include "AVLTree.h"
#include "avl_test.h"
#include <stdlib.h>
#include <math.h>

int isBSTHelper(AVLTreeNode* node, int min, int max) {
    if (node == NULL) {
        return 1;
    }
    if (node->data <= min || node->data >= max) {
        return 0;
    }
    return isBSTHelper(node->left, min, node->data) && isBSTHelper(node->right, node->data, max);
}

int isAVLHelper(AVLTreeNode* node) {
    if (node == NULL) {
        return 1;
    }
    int leftHeight = AVL_Node_Height(node->left);
    int rightHeight = AVL_Node_Height(node->right);

    if (abs(leftHeight - rightHeight) > 1) {
        return 0;
    }
    return isAVLHelper(node->left) && isAVLHelper(node->right);
}

int AVL_IsValid(AVLTree* tree) {
    if (tree == NULL || tree->root == NULL) {
        return 1;
    }
    return isBSTHelper(tree->root, INT_MIN, INT_MAX) && isAVLHelper(tree->root);
}

TEST_FUN_IMPL(AVLTreeTest, ValidAVLTreeInitialization) {
    // Arrange & Act
    AVLTree* tree = AVL_Create();

    // Assert
    TEST_ASSERT(tree != NULL);
    TEST_ASSERT(tree->root == NULL);

    // Cleanup
    AVL_Destroy(tree);
} END_FUN

TEST_FUN_IMPL(AVLTreeTest, AVLTreeInsert) {
    // Arrange
    AVLTree* tree = AVL_Create();
    int values[] = { 10, 20, 30, 5, 4, 40, 35, 15, 13, 2, 3 };

    // Act
    for (int i = 0; i < 11; i++)
        AVL_Insert(tree, values[i]);

    // Assert
    TEST_ASSERT(AVL_IsValid(tree));

    // Cleanup
    AVL_Destroy(tree);
} END_FUN

TEST_FUN_IMPL(AVLTreeTest, AVLTreeInsertAndDelete) {
    // Arrange
    AVLTree* tree = AVL_Create();
    int values[] = { 10, 20, 30, 5, 4, 40, 35, 15, 13, 2, 3 };
    int values2[] = { 13, 16, 3, 6, 9, 7, 28, 21 };

    // Act
    for (int i = 0; i < 11; i++)
        AVL_Insert(tree, values[i]);

    int tempValue;

    tempValue = 10;
    AVL_Remove(tree, tempValue);

    tempValue = 25;
    AVL_Remove(tree, tempValue);

    tempValue = 5;
    AVL_Remove(tree, tempValue);

    for (int i = 0; i < 8; i++)
        AVL_Insert(tree, values2[i]);

    // Assert
    TEST_ASSERT(AVL_IsValid(tree));

    // Cleanup
    AVL_Destroy(tree);
} END_FUN

TEST_FUN_IMPL(AVLTreeTest, AVLTreeInsertDeleteAndCheck) {
    // Arrange
    AVLTree* tree = AVL_Create();
    int values[] = { 10, 20, 30, 5, 4, 40, 35, 15, 13, 2, 3 };

    // Act & Assert
    for (int i = 0; i < 11; i++)
        AVL_Insert(tree, values[i]);

    for (int i = 0; i < 11; i++) {
        AVL_Remove(tree, values[i]);
        TEST_ASSERT(AVL_IsValid(tree));

        AVL_Insert(tree, values[i]);
        TEST_ASSERT(AVL_IsValid(tree));
    }

    // Cleanup
    AVL_Destroy(tree);
} END_FUN

TEST_FUN_IMPL(AVLTreeTest, LargeInsertHeightCheck) {
    // Arrange
    AVLTree* tree = AVL_Create();
    int numElements = 1000;

    // Act
    for (int i = 1; i <= numElements; i++) {
        AVL_Insert(tree, i);
    }

    // Assert
    int expectedHeight = (int)(ceil(log2(numElements + 1)));
    TEST_ASSERT_LE(tree->root->height, expectedHeight, "%d");

    // Cleanup
    AVL_Destroy(tree);
} END_FUN

INIT_TEST_SUITE(AVLTreeTest)
BIND_TEST(AVLTreeTest, ValidAVLTreeInitialization)
BIND_TEST(AVLTreeTest, AVLTreeInsert)
BIND_TEST(AVLTreeTest, AVLTreeInsertAndDelete)
BIND_TEST(AVLTreeTest, AVLTreeInsertDeleteAndCheck)
BIND_TEST(AVLTreeTest, LargeInsertHeightCheck)
END_INIT_TEST_SUITE(AVLTreeTest)