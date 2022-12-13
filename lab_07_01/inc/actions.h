#ifndef __ACTIONS_H__

#define __ACTIONS_H__

#include <stdio.h>
#include <stdlib.h>

#include "binary_tree.h"
#include "scapegoat_tree.h"
#include "hash_table_open.h"
#include "hash_table_close.h"
#include "arr_ints.h"

#define COMMAND_NUMBER_LEN 3

void flush_stdin();
void info_print();
int actions_print();
int actions_handler(int com, hash_table_open_t *table_open, hash_table_close_t *table_close, scapegoat_tree_t *stree, binary_tree_t *btree);
int exec_scan_from_string(hash_table_open_t *table_open, hash_table_close_t *table_close, scapegoat_tree_t *stree, binary_tree_t *btree);
int exec_add(hash_table_open_t *table_open, hash_table_close_t *table_close, scapegoat_tree_t *stree, binary_tree_t *btree);
void exec_del(hash_table_open_t *table_open, hash_table_close_t *table_close, scapegoat_tree_t *stree, binary_tree_t *btree);
void exec_del_ununique(hash_table_open_t *table_open, hash_table_close_t *table_close, scapegoat_tree_t *stree, binary_tree_t *btree);
void exec_print(hash_table_open_t *table_open, hash_table_close_t *table_close, scapegoat_tree_t *stree, binary_tree_t *btree);
void exec_time_cmp_del_ununique();
void exec_time_cmp_del();
void exec_time_cmp_add();
void exec_time_cmp_find();
void exec_mem_cmp();

#endif // #ifndef __ACTIONS_H__
