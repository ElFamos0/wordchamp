#include "tree.h"
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

// Fonction d'initialisation et de destroy

tree_t * tree_init() {
    tree_t *tree = malloc(sizeof(tree_t));
    tree->root = NULL;
    return tree;
}

node_t * node_init() {
    node_t *node = malloc(sizeof(node_t));
    node->left = NULL;
    node->right = NULL;
    node->parent = NULL;
    node->value = 0;
    return node;
}

void tree_destroy(tree_t *tree) {
    if (tree->root) {
        tree_destroy_node(tree->root);
    }
    free(tree);
}

void tree_destroy_node(node_t *node) {
    if (node->left) {
        tree_destroy_node(node->left);
    }
    if (node->right) {
        tree_destroy_node(node->right);
    }
    free(node);
}

// Fonction sur les calculs utiles

void tree_insert(tree_t *tree, int value) {
    node_t *node = node_init();
    node->value = value;
    if (tree->root == NULL) {
        tree->root = node;
    } else {
        node_t *current = tree->root;
        while (current) {
            if (value < current->value) {
                if (current->left == NULL) {
                    current->left = node;
                    node->parent = current;
                    break;
                } else {
                    current = current->left;
                }
            } else {
                if (current->right == NULL) {
                    current->right = node;
                    node->parent = current;
                    break;
                } else {
                    current = current->right;
                }
            }
        }
    }
}

int tree_height(tree_t *tree) {
    if (tree->root) {
        return tree_height_node(tree->root)+1;
    }
    return 0;
}

int tree_height_node(node_t *node) {
    if (node->left == NULL && node->right == NULL) {
        return 0;
    } else {
        int left = 0;
        int right = 0;
        if (node->left) {
            left = tree_height_node(node->left);
        }
        if (node->right) {
            right = tree_height_node(node->right);
        }
        return 1 + (left > right ? left : right);
    }
}

void tree_print_sorted(tree_t *tree) {
    if (tree->root) {
        tree_print_sorted_node(tree->root);
    }
}

void tree_print_sorted_node(node_t *node) {
    if (node->left) {
        tree_print_sorted_node(node->left);
    }
    printf("%d ", node->value);
    if (node->right) {
        tree_print_sorted_node(node->right);
    }
}

node_t * tree_min(tree_t *tree) {
    if (tree->root) {
        return tree_min_node(tree->root);
    }
    return NULL;
}

node_t * tree_min_node(node_t *node) {
    if (node->left) {
        return tree_min_node(node->left);
    }
    return node;
}

node_t * tree_max(tree_t *tree) {
    if (tree->root) {
        return tree_max_node(tree->root);
    }
    return NULL;
}

node_t * tree_max_node(node_t *node) {
    if (node->left) {
        return tree_max_node(node->right);
    }
    return node;
}

node_t * tree_successor(node_t *node) {
    if (node == NULL) {
        return NULL;
    }
    if (node->right) {
        return tree_min_node(node->right);
    } else {
        node_t *current = node;
        while (current->parent) {
            if (current->parent->left == current) {
                return current->parent;
            }
            current = current->parent;
        }
    }
    return NULL;
}

int tree_count_nodes(tree_t *tree) {
    if (tree->root) {
        return tree_count_nodes_node(tree->root);
    }
    return 0;
}

int tree_count_nodes_node(node_t *node) {
    if (node->left == NULL && node->right == NULL) {
        return 1;
    } else {
        int left = 0;
        int right = 0;
        if (node->left) {
            left = tree_count_nodes_node(node->left);
        }
        if (node->right) {
            right = tree_count_nodes_node(node->right);
        }
        return 1 + left + right;
    }
}

int tree_sum(tree_t *tree) {
    if (tree->root) {
        return tree_sum_node(tree->root);
    }
    return 0;
}

int tree_sum_node(node_t *node) {
    if (node->left == NULL && node->right == NULL) {
        return node->value;
    } else {
        int left = 0;
        int right = 0;
        if (node->left) {
            left = tree_sum_node(node->left);
        }
        if (node->right) {
            right = tree_sum_node(node->right);
        }
        return node->value + left + right;
    }
}