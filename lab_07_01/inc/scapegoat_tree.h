#ifndef __SCAPEGOAT_TREE_H__

#define __SCAPEGOAT_TREE_H__

#include <stdio.h>
#include <stdlib.h>

#include "errors_scapegoat_tree.h"

#include "colors.h"
#include "my_time.h"
#include "arr_ints.h"

typedef struct scapegoat_node_t scapegoat_node_t;

struct scapegoat_node_t
{
    int data;
    size_t cnt;
    size_t weight;
    scapegoat_node_t *left;
    scapegoat_node_t *right;
};

typedef struct 
{
    scapegoat_node_t *root;
} scapegoat_tree_t;

typedef struct
{
    size_t size;
    scapegoat_node_t *data;
} nodes_t;

void scapegoat_init(scapegoat_tree_t *tree);
int scapegoat_create_node(scapegoat_node_t *root, scapegoat_node_t **node, int elem);
void scapegoat_clear(scapegoat_node_t *root);
int scapegoat_add(scapegoat_node_t **root, int elem, size_t *cnt, int balance);
void scapegoat_del(scapegoat_node_t **root, int elem);
scapegoat_node_t *scapegoat_rightmost_son(scapegoat_node_t *root, scapegoat_node_t **parent);
scapegoat_node_t **scapegoat_find(scapegoat_node_t **root, int elem);
size_t scapegoat_height(scapegoat_node_t *root);
void scapegoat_flatten_inorder(scapegoat_node_t **root, nodes_t *ptrs);
void scapegoat_build_balanced(scapegoat_node_t **root, nodes_t *ptrs, size_t l, size_t r);
void scapegoat_balance(scapegoat_node_t **root);
size_t scapegoat_find_scapegoat(scapegoat_node_t **root, scapegoat_node_t ***scapegoat);
void scapegoat_del_ununique(scapegoat_node_t **root);
int scapegoat_scan_from(scapegoat_tree_t *tree, arr_ints_t *s);
unsigned long long scapegoat_del_ununique_time(arr_ints_t *s);
unsigned long long scapegoat_add_time(arr_ints_t *s);
unsigned long long scapegoat_del_time(arr_ints_t *s);
unsigned long long scapegoat_find_time(arr_ints_t *s);
void scapegoat_print_level(scapegoat_node_t *root, size_t lvl, nodes_t *nodes);
void scapegoat_print_tree(scapegoat_node_t *root);
void scapegoat_print_postfix(scapegoat_node_t *root);
size_t scapegoat_elem_mem();
size_t scapegoat_struct_mem();


#endif // #ifndef __SCAPEGOAT_TREE_H__
