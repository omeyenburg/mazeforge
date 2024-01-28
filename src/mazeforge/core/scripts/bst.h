#ifndef BST_H
#define BST_H

#include <stdbool.h>

typedef struct Node {
    struct Node* left;
    struct Node* right;
    int value;
    int size;
} Node;

typedef struct BinaryTree {
    Node* root;
    int size;
} BinaryTree;

BinaryTree* bst_create();
void bst_delete(BinaryTree* tree);
void bst_print(BinaryTree* tree);
void bst_insert(BinaryTree* tree, int value);
void bst_remove(BinaryTree* tree, int value);
bool bst_contains(BinaryTree* tree, int value);
int bst_get(BinaryTree* tree, int index);
int bst_get_random(BinaryTree* tree);

#endif // BST_H
