#ifndef TREE_H
#define TREE_H

typedef struct node {
    struct node *left;
    struct node *right;
    struct node *parent;
    int value;
} node_t;

typedef struct tree {
    node_t *root;
} tree_t;

tree_t * tree_init();
node_t * node_init();

void tree_destroy(tree_t *tree);
void tree_destroy_node(node_t *node);

void tree_insert(tree_t *tree, int value);

int tree_height(tree_t *tree);
int tree_height_node(node_t *node);

void tree_print_sorted(tree_t *tree);
void tree_print_sorted_node(node_t *node);

node_t * tree_min(tree_t *tree);
node_t * tree_min_node(node_t *node);

node_t * tree_max(tree_t *tree);
node_t * tree_max_node(node_t *node);

node_t * tree_successor(node_t * node);

int tree_count_nodes(tree_t *tree);
int tree_count_nodes_node(node_t *node);

int tree_sum(tree_t *tree);
int tree_sum_node(node_t *node);

#endif