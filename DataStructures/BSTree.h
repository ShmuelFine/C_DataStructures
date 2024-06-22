#ifndef BSTREE_H
#define BSTREE_H
///////////////////////////////////////////
// Binary Search Tree without balancing. //
///////////////////////////////////////////
#include <stdbool.h>

#define BST_DATA_TYPE int

typedef struct BSTNode {
    BST_DATA_TYPE data;
    struct BSTNode* left, * right;
} BSTNode;

typedef struct {
    BSTNode* root;
} BST;

BST* BST_create();
void BST_free(BST* tree);
bool BST_insert(BST* tree, BST_DATA_TYPE value);
BSTNode* BST_find(BST* tree, BST_DATA_TYPE value);
bool BST_delete(BST* tree, BST_DATA_TYPE value);

#endif // BSTREE_H
