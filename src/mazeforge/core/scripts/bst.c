#include <stdbool.h>
#include <stdlib.h>
#include <stdio.h>
#include "bst.h"


Node* create_node(int value) {
    Node* node = (Node*)malloc(sizeof(Node));
    node->value = value;
    node->exists = true;
    node->lower = node->higher = NULL;
    return node;
}


// Public
// Create and returns an empty binary search tree
BinaryTree* bst_create() {
    BinaryTree* tree = (BinaryTree*)malloc(sizeof(BinaryTree));
    if (tree == NULL) exit(EXIT_FAILURE);
    tree->root = NULL;
    return tree;
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


void recursive_print(const Node* node) {
    if (node == NULL) return;
    recursive_print(node->lower);
    if (node->exists == true) printf("%d\n", node->value);
    recursive_print(node->higher);
}

// Public
// Print values of binary search tree in order
void bst_print(BinaryTree* tree) {
    if (tree->root == NULL) return;
    recursive_print(tree->root);
}


bool recursive_insert(Node* node, int value) {
    if (node->value == value && node->exists == false) {
        node->exists = true;
        return true;
    } else if (node->value == value) {
        return false;
    } else if (node->value > value) {
        if (node->lower == NULL) {
            Node* new_node = create_node(value);
            node->lower = new_node;
            return true;
        } else {
            return recursive_insert(node->lower, value);
        }
    } else {
        if (node->higher == NULL) {
            Node* new_node = create_node(value);
            node->higher = new_node;
            return true;
        } else {
            return recursive_insert(node->higher, value);
        }
    }
}

// Public
// Add value to tree or returns true if value is already in tree
void bst_insert(BinaryTree* tree, int value) {
    if (tree->root == NULL) {
        Node* node = create_node(value);
        tree->root = node;
        tree->size = 1;
    } else {
        if (recursive_insert(tree->root, value) == true) {
            tree->size++;
        }
    }
}


bool recursive_remove(Node* node, Node* parent, int value) {
    if (node->value == value) {
        bool removed = node->exists;
        if (parent != NULL && node->lower == NULL && node->higher == NULL) {
            if (parent->lower != NULL && node->value == parent->lower->value) {
                parent->lower = NULL;
            } else {
                parent->higher = NULL;
            }
            free(node);
        } else {
            node->exists = false;
        }
        return removed;
    } else if (node->value > value) {
        if (node->lower == NULL) return false;
        return recursive_remove(node->lower, node, value);
    } else {
        if (node->higher == NULL) return false;
        return recursive_remove(node->higher, node, value);
    }
}

// Public
// Remove a value from a binary search tree
void bst_remove(BinaryTree* tree, int value) {
    if (tree->root == NULL) return;
    if (recursive_remove(tree->root, NULL, value) == true) {
        tree->size--;
    }
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


int recursive_get_lower(Node* node, int* index) {
    if (node->lower != NULL) {
        int value = recursive_get_lower(node->lower, index); // Go down left
        if (*index == -1) {
            return value;
        }
    }
    if (node->exists == true) {
        --*index; // Decrease index
        if (*index == -1) {
            return node->value;
        }
    }
    if (node->higher != NULL) {
        return recursive_get_lower(node->higher, index); // Go down right
    }
    return 0;
}

int recursive_get_higher(Node* node, int* index) {
    if (node->higher != NULL) {
        int value = recursive_get_higher(node->higher, index); // Go down right
        if (*index == -1) {
            return value;
        }
    }
    if (node->exists == true) {
        --*index; // Decrease index
        if (*index == -1) {
            return node->value;
        }
    }
    if (node->lower != NULL) {
        return recursive_get_higher(node->lower, index); // Go down left
    }
    return 0;
}


// Public
// Retrieve the value at an index
int bst_get(BinaryTree* tree, int index) {
    if (tree->root == NULL || index >= tree->size || index < -tree->size + 1) return -1;
    if (index < 0) {
        index += tree->size;
    }
    if (index * 2 < tree->size) {
        return recursive_get_lower(tree->root, &index);
    } else {
        index = tree->size - index - 1;
        return recursive_get_higher(tree->root, &index);
    }
}


// Public
// Return a random value from a binary search tree
int bst_get_random(BinaryTree* tree) {
    int index = rand() % tree->size;
    return bst_get(tree, index);
}
