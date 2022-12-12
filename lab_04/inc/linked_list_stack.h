#ifndef __LINKED_LIST_STACK_H__

#define __LINKED_LIST_STACK_H__

#include <stdio.h>
#include <stdlib.h>

#include "stack.h"

#include "errors_linked_list_stack.h"

#include "my_time.h"

#define LINKED_LIST_STACK_SIZE_ELEM sizeof(node_t)
#define LINKED_LIST_STACK_FREED_ADDRS_SIZE 100

typedef struct
{
    size_t size;
    void *data[LINKED_LIST_STACK_FREED_ADDRS_SIZE];
} addrs;

typedef struct node_t node_t;

struct node_t
{
    int data;
    node_t *next;
};

typedef struct
{
    node_t *head;
} linked_list_stack_t;

void linkedstack_addrs_add(addrs *freed_addrs, void *addr);
void linkedstack_addrs_del(addrs *freed_addrs, void *addr);
void linkedstack_addrs_print(addrs *freed_addrs);
int linkedstack_empty(void *stack);
void linkedstack_init(linked_list_stack_t *stack);
int linkedstack_scan(linked_list_stack_t *stack, addrs *freed_addrs);
int linkedstack_print(linked_list_stack_t *stack, addrs *freed_addrs);
int linkedstack_add(linked_list_stack_t *stack, int elem, addrs *freed_addrs);
void linkedstack_clear_node(node_t *node);
int linkedstack_pop(linked_list_stack_t *stack, int *last, void **addr, addrs *freed_addrs);
int linkedstack_cmp_node(node_t *n1, node_t *n2);
int linkedstack_clear(linked_list_stack_t *stack, addrs *freed_addrs);
int linkedstack_move(linked_list_stack_t *dst, linked_list_stack_t *src, addrs *freed_addrs);
int linkedstack_sort_descending(linked_list_stack_t *stack, addrs *freed_addrs);
int linkedstack_merge(linked_list_stack_t *src1, linked_list_stack_t *src2, linked_list_stack_t *dst, addrs *freed_addrs);
int linkedstack_to(linked_list_stack_t *src, mystack_t *dst, addrs *freed_addrs);
int linkedstack_from(linked_list_stack_t *dst, mystack_t *src, addrs *freed_addrs);
int linkedstack_copy(linked_list_stack_t *src, linked_list_stack_t *copy, addrs *freed_addrs);
int linkedstack_from_arr(linked_list_stack_t *dst, int arr[], size_t n, addrs *freed_addrs);
unsigned long long linkedstack_sort_merge_time(linked_list_stack_t *stack1, linked_list_stack_t *stack2, addrs *freed_addrs);
size_t linkedstack_mem(linked_list_stack_t *stack, addrs *freed_addrs);

#endif // #ifndef __LINKED_LIST_STACK_H__
