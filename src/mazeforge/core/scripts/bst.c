#include "bst.h"
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

Node *create_node(int value) {
    Node *node = (Node *)malloc(sizeof(Node));
    node->left = node->right = NULL;
    node->value = value;
    node->size = 0;
    return node;
}

// Public
// Create and returns an empty binary search tree
BinaryTree *bst_create() {
    BinaryTree *tree = (BinaryTree *)malloc(sizeof(BinaryTree));
    if (tree == NULL)
        exit(EXIT_FAILURE);
    tree->root = NULL;
    return tree;
}

void recursive_delete(Node *node) {
    if (node == NULL)
        return;
    recursive_delete(node->left);
    recursive_delete(node->right);
    free(node);
}

// Public
// Delete and deallocate binary search tree
void bst_delete(BinaryTree *tree) {
    if (tree->root != NULL)
        recursive_delete(tree->root);
    free(tree);
}

void recursive_print_values(const Node *node) {
    if (node == NULL)
        return;
    recursive_print_values(node->left);
    printf("%d\n", node->value);
    recursive_print_values(node->right);
}

// Public
// Print values of a binary search tree in order
void bst_print_values(BinaryTree *tree) {
    if (tree->root == NULL)
        return;
    recursive_print_values(tree->root);
}

void recursive_print(Node *node, int indentation) {
    if (node == NULL)
        return;
    printf("|");
    for (int i = 0; i < indentation; i++) {
        printf("        ");
    }
    printf("- %d (%d children)\n", node->value, node->size);
    indentation++;
    recursive_print(node->left, indentation);
    recursive_print(node->right, indentation);
}

// Public
// Print the structure of a binary search tree
void bst_print(BinaryTree *tree) {
    printf("| Binary Search Tree Structure (%d children)\n", tree->size);
    if (tree->root == NULL)
        return;
    recursive_print(tree->root, 0);
}

bool recursive_insert(Node *node, int value) {
    if (node->value == value) {
        return false;
    } else if (node->value > value) {
        if (node->left == NULL) {
            Node *new_node = create_node(value);
            node->left = new_node;
            node->size++;
            return true;
        } else {
            if (recursive_insert(node->left, value) == true) {
                node->size++;
                return true;
            }
            return false;
        }
    } else {
        if (node->right == NULL) {
            Node *new_node = create_node(value);
            node->right = new_node;
            node->size++;
            return true;
        } else {
            if (recursive_insert(node->right, value) == true) {
                node->size++;
                return true;
            }
            return false;
        }
    }
}

// Public
// Add value to tree or returns true if value is already in tree
void bst_insert(BinaryTree *tree, int value) {
    if (tree->root == NULL) {
        Node *node = create_node(value);
        tree->root = node;
        tree->size = 1;
    } else {
        if (recursive_insert(tree->root, value) == true) {
            tree->size++;
        }
    }
}

bool recursive_remove(Node **link, int value) {
    Node *node = *link;

    if (node == NULL) {
        return false;
    }

    if (node->value > value) {
        if (recursive_remove(&node->left, value) == true) {
            node->size--;
            return true;
        }
        return false;
    } else if (node->value < value) {
        if (recursive_remove(&node->right, value) == true) {
            node->size--;
            return true;
        }
        return false;
    }

    if (node->left == NULL) {
        // Lower or both are NULL
        Node *temp = node;
        *link = node->right; // Update parent's reference
        free(temp);
    } else if (node->right == NULL) {
        // Higher is NULL
        Node *temp = node;
        *link = node->left; // Update parent's reference
        free(temp);
    } else {
        // None are NULL
        Node *successor = node->right;
        while (successor->left != NULL) {
            successor = successor->left;
        }
        node->value = successor->value;
        recursive_remove(&node->right, successor->value);
        node->size = 0;
        if (node->left != NULL) {
            node->size += 1 + node->left->size;
        }
        if (node->right != NULL) {
            node->size += 1 + node->right->size;
        }
    }
    return true;
}

// Public
// Remove a value from a binary search tree
void bst_remove(BinaryTree *tree, int value) {
    if (tree->root == NULL)
        return;
    if (recursive_remove(&tree->root, value) == true) {
        tree->size--;
    }
}

bool recursive_contains(Node *node, int value) {
    if (node->value == value) {
        return true;
    } else if (node->value > value) {
        if (node->left == NULL)
            return false;
        return recursive_contains(node->left, value);
    } else {
        if (node->right == NULL)
            return false;
        return recursive_contains(node->right, value);
    }
}

// Public
// Returns bool(value ∈ tree)
bool bst_contains(BinaryTree *tree, int value) {
    if (tree->root == NULL)
        return false;
    return recursive_contains(tree->root, value);
}

int recursive_get_lower(Node *node, int *index) {
    if (node->left != NULL) {
        int value = recursive_get_lower(node->left, index); // Go down left
        if (*index == -1) {
            return value;
        }
    }

    --*index; // Decrease index
    if (*index == -1) {
        return node->value;
    }

    if (node->right != NULL) {
        return recursive_get_lower(node->right, index); // Go down right
    }
    return 0;
}

int recursive_get_higher(Node *node, int *index) {
    if (node->right != NULL) {
        int value = recursive_get_higher(node->right, index); // Go down right
        if (*index == -1) {
            return value;
        }
    }

    --*index; // Decrease index
    if (*index == -1) {
        return node->value;
    }

    if (node->left != NULL) {
        return recursive_get_higher(node->left, index); // Go down left
    }
    return 0;
}

// Public
// Retrieve the value at an index
int bst_get2(BinaryTree *tree, int index) {
    if (tree->root == NULL || index >= tree->size || index < -tree->size + 1)
        return -1;
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

int recursive_get(Node *node, int index) {
    if (node == NULL) {
    }
    if (node->size == 0) {
        return node->value;
    }
    if (node->left != NULL) {
        if (node->left->size >= index) {
            return recursive_get(node->left, index);
        } else if (node->left->size == index - 1) {
            return node->value;
        } else {
            return recursive_get(node->right, index - node->left->size - 2);
        }
    }
    if (index == 0) {
        return node->value;
    }
    return recursive_get(node->right, index - 1);
}

int bst_get(BinaryTree *tree, int index) {
    if (tree->root == NULL || index >= tree->size || index < -tree->size + 1)
        return -1;
    if (index < 0) {
        index += tree->size;
    }
    return recursive_get(tree->root, index);
}

// Public
// Return a random value from a binary search tree
int bst_get_random(BinaryTree *tree) {
    int index = rand() % tree->size;
    return bst_get(tree, index);
}

int main() {
    BinaryTree *tree = bst_create();
    bst_insert(tree, 50);
    bst_insert(tree, 60);
    bst_insert(tree, 20);
    bst_insert(tree, 25);
    bst_insert(tree, 70);
    bst_insert(tree, 40);
    bst_insert(tree, 22);
    bst_insert(tree, 13);
    bst_insert(tree, 80);
    bst_print(tree);
    bst_print_values(tree);

    for (int i = 0; i < tree->size; i++) {
        printf("val %d\n", bst_get(tree, i));
        bst_print(tree);
    }
    bst_delete(tree);
    return 0;

    bst_remove(tree, 50);
    bst_remove(tree, 25);
    bst_print(tree);
    bst_print_values(tree);
    for (int i = 0; i < 10; i++) {
        printf("%d\n", bst_get(tree, i));
    }

    while (tree->size != 0) {
        int cell = bst_get_random(tree);
        if (cell == -1) {
            break;
        }
        bst_remove(tree, cell);
        bst_print(tree);
    }

    bst_delete(tree);
    return 0;
}