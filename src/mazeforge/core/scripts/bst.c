#include "bst.h"
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>


Node* create_node(int value) {
    Node* node = (Node*)malloc(sizeof(Node));
    node->value = value;
    node->exists = NULL;
    node->lower = node->higher = NULL;
    return node;
}


// Public
// Creates and returns an empty binary search tree
BinaryTree* bst_create() {
    BinaryTree* tree = (BinaryTree*)malloc(sizeof(BinaryTree));
    if (tree == NULL) {
        exit(EXIT_FAILURE);
    }
    tree->root = NULL;
    return tree;
}


void recursive_insert(Node* node, int value) {
    if (node->value == value) {
        node->exists = true;
    } else if (node->value > value) {
        if (node->lower == NULL) {
            Node* new_node = create_node(value);
            node->lower = new_node;
        } else {
            recursive_insert(node->lower, value);
        }
    } else {
        if (node->higher == NULL) {
            Node* new_node = create_node(value);
            node->higher = new_node;
        } else {
            recursive_insert(node->higher, value);
        }
    }
}

// Public
// Adds value to tree or returns true if value is already in tree
void bst_insert(BinaryTree* tree, int value) {
    if (tree->root == NULL) {
        Node* node = create_node(value);
        tree->root = node;
    } else {
        recursive_insert(tree->root, value);
    }
}


void recursive_remove(Node* node, Node* parent, int value) {
    if (node->value == value) {
        
        if (parent != NULL && node->lower == NULL && node->higher == NULL) {
            if (node->value == parent->lower->value) {
                parent->lower = NULL;
            } else {
                parent->higher = NULL;
            }
            free(node);
        } else {
            node->exists = false;
        }
    } else if (node->value > value) {
        if (node->lower == NULL) return;
        recursive_remove(node->lower, node, value);
    } else {
        if (node->higher == NULL) return;
        recursive_remove(node->higher, node, value);
    }
}

// Public
void bst_remove(BinaryTree* tree, int value) {
    if (tree->root == NULL) return;
    recursive_remove(tree->root, NULL, value); 
}


bool recursive_contains(Node* node, int value) {
    if (node->value == value) {
        return node->exists == true;
    } else if (node->value > value) {
        if (node->lower == NULL) return false;
        return recursive_contains(node->lower, value);
    } else {
        if (node->higher == NULL) return false;
        return recursive_contains(node->higher, value);
    }
}

// Public
// Returns bool(value ∈ tree)
bool bst_contains(BinaryTree* tree, int value) {
    if (tree->root == NULL) return false;
    return recursive_contains(tree->root, value); 
}

void recursive_print(const Node* node) {
    if (node == NULL) return;
    printf("lower\n");
    recursive_print(node->lower);
    if (node->exists == true) printf("%d\n", node->value);
    printf("higher\n");
    recursive_print(node->higher);
}

// Public
// Print values of binary search tree in order
void bst_print(BinaryTree* tree) {
    if (tree->root == NULL) return;
    recursive_print(tree->root);
}

void recursive_delete(Node* node) {
    if (node == NULL) return;
    recursive_delete(node->lower);
    recursive_delete(node->higher);
    free(node);
}

// Public
// Delete and deallocate binary search tree
void bst_delete(BinaryTree* tree) {
    if (tree->root != NULL) recursive_delete(tree->root);
    free(tree);
}
