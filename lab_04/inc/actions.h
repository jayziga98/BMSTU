#ifndef __ACTIONS_H__

#define __ACTIONS_H__

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "stack.h"
#include "linked_list_stack.h"
#include "data_generator.h"

#define COMMAND_NUMBER_LEN 3
#define STACK_TYPE_LEN 50
#define TIME_TABLE_NUM_LEN 9

#define STACK_TYPE_CLASSIC "Классический"
#define STACK_TYPE_LINKED_LIST "Связный список"

void info_print();
int actions_print(char type[STACK_TYPE_LEN]);
int actions_handler(int com, mystack_t *stack1, mystack_t *stack2, mystack_t *stack3, linked_list_stack_t *llstack1, linked_list_stack_t *llstack2, linked_list_stack_t *llstack3, char type[STACK_TYPE_LEN], addrs *freed_addrs);
int exec_change_stack_type(mystack_t *stack1, mystack_t *stack2, mystack_t *stack3, linked_list_stack_t *llstack1, linked_list_stack_t *llstack2, linked_list_stack_t *llstack3, char type[STACK_TYPE_LEN], addrs *freed_addrs);
int exec_scan(mystack_t *stack, linked_list_stack_t *llstack, char type[STACK_TYPE_LEN], addrs *freed_addrs);
int exec_print(mystack_t *stack, linked_list_stack_t *llstack, char type[STACK_TYPE_LEN], addrs *freed_addrs, int copy);
int exec_add(mystack_t *stack, linked_list_stack_t *llstack, char type[STACK_TYPE_LEN], addrs *freed_addrs);
int exec_pop(mystack_t *stack, linked_list_stack_t *llstack, char type[STACK_TYPE_LEN], addrs *freed_addrs);
int exec_merge_sort(mystack_t *stack1, mystack_t *stack2, mystack_t *stack3, linked_list_stack_t *llstack1, linked_list_stack_t *llstack2, linked_list_stack_t *llstack3, char type[STACK_TYPE_LEN], addrs *freed_addrs);
void time_cmp_by(size_t n, void (fill_arr1)(int *, size_t n), void (fill_arr2)(int *, size_t n), addrs *freed_addrs);
void exec_time_cmp(addrs *freed_addrs);
void exec_mem_cmp(addrs *freed_addrs);
void exec_print_freed(addrs *freed_addrs);

#endif // #ifndef __ACTIONS_H__
