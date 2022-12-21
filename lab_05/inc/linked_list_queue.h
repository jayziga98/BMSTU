#ifndef __LINKED_LIST_QUEUE_H__

#define __LINKED_LIST_QUEUE_H__

#include <stdio.h>
#include <stdlib.h>

#include "errors_linked_list_queue.h"

#include "my_time.h"

typedef struct node_t node_t;

struct node_t
{
    int data;
    node_t *next;
};

typedef struct
{
    node_t *head;
    node_t *tail;
} queue_linked_list_t;

int queue_linked_list_empty(void *q);
void queue_linked_list_init(void *q);
int queue_linked_list_create_node(void *q);
void queue_linked_list_clear(void *q, int addrs);
int queue_linked_list_add(void *q, int elem, int addrs);
int queue_linked_list_pop(void *q, int *elem, int addrs);
void queue_linked_list_print(void *q, int addrs);
void print_debug_ll(void *q);
void queue_linked_list_add_time();

#endif // #ifndef __LINKED_LIST_QUEUE_H__
