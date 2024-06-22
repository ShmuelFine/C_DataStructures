#include "BSTree.h"
#include <stdlib.h>

BST* BST_create() {
    BST* tree = (BST*)malloc(sizeof(BST));
    if (tree) {
        tree->root = NULL;
    }
    return tree;
}

void BST_free_node(BSTNode* node) {
    if (node) {
        BST_free_node(node->left);
        BST_free_node(node->right);
        free(node);
    }
}

void BST_free(BST* tree) {
    if (tree) {
        BST_free_node(tree->root);
        free(tree);
    }
}

BSTNode* BST_insert_node(BSTNode* node, BST_DATA_TYPE value) {
    if (!node) {
        node = (BSTNode*)malloc(sizeof(BSTNode));
        if (node) {
            node->data = value;
            node->left = node->right = NULL;
        }
    }
    else if (value < node->data) {
        node->left = BST_insert_node(node->left, value);
    }
    else if (value > node->data) {
        node->right = BST_insert_node(node->right, value);
    }
    return node;
}

bool BST_insert(BST* tree, BST_DATA_TYPE value) {
    if (!tree) return false;
    tree->root = BST_insert_node(tree->root, value);
    return true;
}

BSTNode* BST_find_node(BSTNode* node, BST_DATA_TYPE value) {
    if (!node) return NULL;
    if (value == node->data) return node;
    if (value < node->data) return BST_find_node(node->left, value);
    return BST_find_node(node->right, value);
}

BSTNode* BST_find(BST* tree, BST_DATA_TYPE value) {
    if (!tree) return NULL;
    return BST_find_node(tree->root, value);
}

BSTNode* BST_find_min(BSTNode* node) {
    BSTNode* current = node;
    while (current && current->left != NULL) {
        current = current->left;
    }
    return current;
}

BSTNode* BST_delete_node(BSTNode* root, BST_DATA_TYPE value) {
    if (root == NULL) return root;

    if (value < root->data) {
        root->left = BST_delete_node(root->left, value);
    }
    else if (value > root->data) {
        root->right = BST_delete_node(root->right, value);
    }
    else {
        if (root->left == NULL) {
            BSTNode* temp = root->right;
            free(root);
            return temp;
        }
        else if (root->right == NULL) {
            BSTNode* temp = root->left;
            free(root);
            return temp;
        }

        BSTNode* temp = BST_find_min(root->right);
        root->data = temp->data;
        root->right = BST_delete_node(root->right, temp->data);
    }
    return root;
}

bool BST_delete(BST* tree, BST_DATA_TYPE value) {
    if (!tree) return false;
    tree->root = BST_delete_node(tree->root, value);
    return true;
}
