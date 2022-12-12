#ifndef __BINARY_TREE_H__

#define __BINARY_TREE_H__

#include <stdio.h>
#include <stdlib.h>

#include "errors_binary_tree.h"

#include "colors.h"
#include "my_time.h"
#include "arr_ints.h"

typedef struct btree_node_t btree_node_t;

struct btree_node_t
{
    int data;
    size_t cnt;
    size_t weight;
    btree_node_t *left;
    btree_node_t *right;
};

typedef struct 
{
    btree_node_t *root;
} binary_tree_t;

typedef struct
{
    size_t size;
    btree_node_t *data;
} btree_nodes_t;

void btree_init(binary_tree_t *tree);
int btree_create_node(btree_node_t *root, btree_node_t **node, int elem);
void btree_clear(btree_node_t *root);
int btree_add(btree_node_t **root, int elem, size_t *cnt);
void btree_del(btree_node_t **root, int elem);
btree_node_t *btree_rightmost_son(btree_node_t *root, btree_node_t **parent);
btree_node_t **btree_find(btree_node_t **root, int elem);
size_t btree_height(btree_node_t *root);
void btree_del_ununique(btree_node_t **root);
int btree_scan_from(binary_tree_t *tree, arr_ints_t *s);
unsigned long long btree_del_ununique_time(arr_ints_t *s);
unsigned long long btree_add_time(arr_ints_t *s);
unsigned long long btree_del_time(arr_ints_t *s);
unsigned long long btree_find_time(arr_ints_t *s);
void btree_get_level(btree_node_t *root, size_t lvl, int left, int right, btree_nodes_t *nodes);
void btree_print_tree(btree_node_t *root);
void btree_print_postfix(btree_node_t *root);
size_t btree_elem_mem();
size_t btree_struct_mem();


#endif // #ifndef __BINARY_TREE_H__
