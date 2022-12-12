#ifndef __ACTIONS_H__

#define __ACTIONS_H__

#include <stdio.h>
#include <stdlib.h>

#include "scapegoat_tree.h"
#include "my_string.h"

#define COMMAND_NUMBER_LEN 3

void info_print();
int actions_print();
int actions_handler(int com, binary_tree_t *tree);
int exec_scapegoat_scan_from(binary_tree_t *tree);
void exec_print_unique_postfix(binary_tree_t *tree);
int exec_add(binary_tree_t *tree);
void exec_del(binary_tree_t *tree);
void exec_print_unique_postfix(binary_tree_t *tree);
void exec_time_cmp_del_ununique();
void exec_time_cmp_add();
void exec_time_cmp_del();
void exec_time_cmp_find();
void exec_mem_cmp();

#endif // #ifndef __ACTIONS_H__
