#ifndef __STACK_H__

#define __STACK_H__

#include <stdio.h>
#include <stdlib.h>

#include "errors_stack.h"

#include "my_time.h"

#define STACK_SIZE_ELEM sizeof(int)

typedef struct
{
    size_t size;
    int *head;
    int *data;
} mystack_t;

int stack_empty(void *stack);
void stack_init(mystack_t *stack);
int stack_scan(mystack_t *stack);
int stack_print(mystack_t *stack);
int stack_add(mystack_t *stack, int elem);
int stack_pop(mystack_t *stack, int *last);
void stack_clear(mystack_t *stack);
int stack_move(mystack_t *dst, mystack_t *src);
int stack_copy(mystack_t *src, mystack_t *copy);
int stack_sort_descending(mystack_t *stack);
int stack_merge(mystack_t *src1, mystack_t *src2, mystack_t *dst);
int stack_from_arr(mystack_t *dst, int arr[], size_t n);
unsigned long long stack_sort_merge_time(mystack_t *stack1, mystack_t *stack2);
size_t stack_mem(mystack_t *stack);

#endif // #ifndef __STACK_H__
