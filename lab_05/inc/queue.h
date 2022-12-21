#ifndef __QUEUE_H__

#define __QUEUE_H__

#include <stdio.h>
#include <stdlib.h>

#include "errors_queue.h"

#include "my_time.h"

typedef struct
{
    size_t allocated;
    int *head;
    int *tail;
    int *begin;
    int *end;
    int *data;
} queue_std_t;

int queuestd_empty(void *q);
void queuestd_init(void *q);
int queuestd_create(void *q, size_t n_elems);
int queuestd_fill_order(void *q, size_t n_elems, int addrs);
void queuestd_clear(void *q, int addrs);
void queuestd_tail_rshift(void *q);
void queuestd_head_rshift(void *q);
int queuestd_add(void *q, int elem, int addrs);
int queuestd_pop(void *q, int *elem, int addrs);
void queuestd_print(void *q, int addrs);
void print_debug(void *q);
void queuestd_add_time();

#endif // #ifndef __QUEUE_H__
