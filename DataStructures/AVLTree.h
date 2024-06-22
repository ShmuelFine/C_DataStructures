#ifndef AVLTREE_H
#define AVLTREE_H

#include <stdlib.h>

#define AVL_TREE_DATA_TYPE int

typedef struct AVLTreeNode {
    AVL_TREE_DATA_TYPE data;
    struct AVLTreeNode* left;
    struct AVLTreeNode* right;
    int height;
} AVLTreeNode;

int AVL_Node_Height(AVLTreeNode* node);

typedef struct {
    AVLTreeNode* root;
} AVLTree;

AVLTree* AVL_Create();
void AVL_Destroy(AVLTree* tree);
int AVL_Insert(AVLTree* tree, AVL_TREE_DATA_TYPE data);
int AVL_Search(AVLTree* tree, AVL_TREE_DATA_TYPE data);
int AVL_Remove(AVLTree* tree, AVL_TREE_DATA_TYPE data);

#endif // AVLTREE_H
