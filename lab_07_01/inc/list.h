#ifndef __LIST_H__

#define __LIST_H__

#include <stdio.h>
#include <stdlib.h>

#include "errors_list.h"

#include "my_time.h"
#include "colors.h"

typedef struct node_t node_t;

typedef struct
{
    int letter;
    size_t count;
} hash_table_open_data_t;

struct node_t
{
    hash_table_open_data_t data;
    node_t *next;
};

typedef struct
{
    size_t size;
    node_t *head;
} list_t;

int list_empty(list_t *list);
void list_init(list_t *list);
int list_add(list_t *list, hash_table_open_data_t *elem);
int list_pop(list_t *list, hash_table_open_data_t *last);
void list_del_by(list_t *list, hash_table_open_data_t *elem);
void list_del_ununique(list_t *list);
void list_add_by(list_t *list, hash_table_open_data_t *elem);
size_t list_count(list_t *list, int elem);
int list_clear(list_t *list);
void list_print(list_t *list, char sep, char end);
size_t list_mem(list_t *list);

#endif // #ifndef __LIST_H__
