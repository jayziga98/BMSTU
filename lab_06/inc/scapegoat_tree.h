#ifndef __SCAPEGOAT_TREE_H__

#define __SCAPEGOAT_TREE_H__

#include <stdio.h>
#include <stdlib.h>

#include "errors_scapegoat_tree.h"

#include "colors.h"
#include "my_time.h"
#include "my_string.h"

typedef struct node_t node_t;

struct node_t
{
    char data;
    size_t cnt;
    size_t weight;
    node_t *left;
    node_t *right;
};

typedef struct 
{
    node_t *root;
} binary_tree_t;

typedef struct
{
    size_t size;
    node_t *data;
} nodes_t;

void scapegoat_init(binary_tree_t *tree);
int scapegoat_create_node(node_t *root, node_t **node, char elem);
void scapegoat_clear(node_t *root);
int scapegoat_add(node_t **root, char elem, size_t *cnt, int balance);
void scapegoat_del(node_t **root, char elem);
node_t *scapegoat_rightmost_son(node_t *root, node_t **parent);
node_t **scapegoat_find(node_t **root, char elem);
size_t scapegoat_height(node_t *root);
void scapegoat_flatten_inorder(node_t **root, nodes_t *ptrs);
void scapegoat_build_balanced(node_t **root, nodes_t *ptrs, size_t l, size_t r);
void scapegoat_balance(node_t **root);
size_t scapegoat_find_scapegoat(node_t **root, node_t ***scapegoat);
void scapegoat_del_ununique(node_t **root);
unsigned long long scapegoat_del_ununique_time(my_string_t s);
unsigned long long scapegoat_add_time(my_string_t s);
unsigned long long scapegoat_del_time(my_string_t s);
unsigned long long scapegoat_find_time(my_string_t s);
void scapegoat_print_level(node_t *root, size_t lvl, nodes_t *nodes);
void scapegoat_print_tree(node_t *root);
void scapegoat_print_postfix(node_t *root);
void scapegoat_print_prefix(node_t *root);
void scapegoat_print_infix(node_t *root);


#endif // #ifndef __SCAPEGOAT_TREE_H__
