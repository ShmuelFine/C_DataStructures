#include "AVLTree.h"

AVL_TREE_DATA_TYPE AVL_Node_Max(AVL_TREE_DATA_TYPE a, AVL_TREE_DATA_TYPE b) {
    return (a > b) ? a : b;
}

int AVL_Node_Height(AVLTreeNode* node) {
    return node ? node->height : 0;
}

AVLTreeNode* AVL_Node_Create(AVL_TREE_DATA_TYPE data) {
    AVLTreeNode* node = (AVLTreeNode*)malloc(sizeof(AVLTreeNode));
    node->data = data;
    node->left = node->right = NULL;
    node->height = 1;
    return node;
}

void AVL_Node_Destroy(AVLTreeNode* node) {
    if (node) {
        AVL_Node_Destroy(node->left);
        AVL_Node_Destroy(node->right);
        free(node);
    }
}

AVLTreeNode* AVL_Node_RightRotate(AVLTreeNode* y) {
    AVLTreeNode* x = y->left;
    AVLTreeNode* T2 = x->right;

    x->right = y;
    y->left = T2;

    y->height = AVL_Node_Max(AVL_Node_Height(y->left), AVL_Node_Height(y->right)) + 1;
    x->height = AVL_Node_Max(AVL_Node_Height(x->left), AVL_Node_Height(x->right)) + 1;

    return x;
}

AVLTreeNode* AVL_Node_LeftRotate(AVLTreeNode* x) {
    AVLTreeNode* y = x->right;
    AVLTreeNode* T2 = y->left;

    y->left = x;
    x->right = T2;

    x->height = AVL_Node_Max(AVL_Node_Height(x->left), AVL_Node_Height(x->right)) + 1;
    y->height = AVL_Node_Max(AVL_Node_Height(y->left), AVL_Node_Height(y->right)) + 1;

    return y;
}

int AVL_Node_GetBalance(AVLTreeNode* node) {
    return node ? AVL_Node_Height(node->left) - AVL_Node_Height(node->right) : 0;
}

AVLTreeNode* AVL_Node_Insert(AVLTreeNode* node, AVL_TREE_DATA_TYPE data) {
    if (!node) return AVL_Node_Create(data);

    if (data < node->data)
        node->left = AVL_Node_Insert(node->left, data);
    else if (data > node->data)
        node->right = AVL_Node_Insert(node->right, data);
    else
        return node;

    node->height = AVL_Node_Max(AVL_Node_Height(node->left), AVL_Node_Height(node->right)) + 1;

    int balance = AVL_Node_GetBalance(node);

    if (balance > 1 && data < node->left->data)
        return AVL_Node_RightRotate(node);

    if (balance < -1 && data > node->right->data)
        return AVL_Node_LeftRotate(node);

    if (balance > 1 && data > node->left->data) {
        node->left = AVL_Node_LeftRotate(node->left);
        return AVL_Node_RightRotate(node);
    }

    if (balance < -1 && data < node->right->data) {
        node->right = AVL_Node_RightRotate(node->right);
        return AVL_Node_LeftRotate(node);
    }

    return node;
}

AVLTreeNode* AVL_Node_MinValueNode(AVLTreeNode* node) {
    AVLTreeNode* current = node;
    while (current->left != NULL)
        current = current->left;
    return current;
}

AVLTreeNode* AVL_Node_Remove(AVLTreeNode* root, AVL_TREE_DATA_TYPE data) {
    if (!root) return root;

    if (data < root->data)
        root->left = AVL_Node_Remove(root->left, data);
    else if (data > root->data)
        root->right = AVL_Node_Remove(root->right, data);
    else {
        if (!root->left || !root->right) {
            AVLTreeNode* temp = root->left ? root->left : root->right;
            if (!temp) {
                temp = root;
                root = NULL;
            }
            else
                *root = *temp;
            free(temp);
        }
        else {
            AVLTreeNode* temp = AVL_Node_MinValueNode(root->right);
            root->data = temp->data;
            root->right = AVL_Node_Remove(root->right, temp->data);
        }
    }

    if (!root) return root;

    root->height = AVL_Node_Max(AVL_Node_Height(root->left), AVL_Node_Height(root->right)) + 1;

    int balance = AVL_Node_GetBalance(root);

    if (balance > 1 && AVL_Node_GetBalance(root->left) >= 0)
        return AVL_Node_RightRotate(root);

    if (balance > 1 && AVL_Node_GetBalance(root->left) < 0) {
        root->left = AVL_Node_LeftRotate(root->left);
        return AVL_Node_RightRotate(root);
    }

    if (balance < -1 && AVL_Node_GetBalance(root->right) <= 0)
        return AVL_Node_LeftRotate(root);

    if (balance < -1 && AVL_Node_GetBalance(root->right) > 0) {
        root->right = AVL_Node_RightRotate(root->right);
        return AVL_Node_LeftRotate(root);
    }

    return root;
}

int AVL_Node_Search(AVLTreeNode* root, AVL_TREE_DATA_TYPE data) {
    if (!root) return 0;
    if (data < root->data)
        return AVL_Node_Search(root->left, data);
    else if (data > root->data)
        return AVL_Node_Search(root->right, data);
    else
        return 1;
}

AVLTree* AVL_Create() {
    AVLTree* tree = (AVLTree*)malloc(sizeof(AVLTree));
    tree->root = NULL;
    return tree;
}

void AVL_Destroy(AVLTree* tree) {
    AVL_Node_Destroy(tree->root);
    free(tree);
}

int AVL_Insert(AVLTree* tree, AVL_TREE_DATA_TYPE data) {
    tree->root = AVL_Node_Insert(tree->root, data);
    return 1;
}

int AVL_Search(AVLTree* tree, AVL_TREE_DATA_TYPE data) {
    return AVL_Node_Search(tree->root, data);
}

int AVL_Remove(AVLTree* tree, AVL_TREE_DATA_TYPE data) {
    tree->root = AVL_Node_Remove(tree->root, data);
    return 1;
}
