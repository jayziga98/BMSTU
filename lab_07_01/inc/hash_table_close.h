#ifndef __HASH_TABLE_CLOSE_H__

#define __HASH_TABLE_CLOSE_H__

#include <stdio.h>
#include <stdlib.h>

#include "errors_hash_table_close.h"

#include "arr_ints.h"
#include "my_time.h"
#include "prime.h"
#include "colors.h"

#define HASH_TABLE_CLOSE_DEFAULT_DIVISOR 151
#define HASH_TABLE_CLOSE_COLLISION_CNT 4

typedef struct
{
    int cnt;
    int data;
} hash_table_close_cell_t;


typedef struct
{
    hash_table_close_cell_t *data;
    int divisor;
} hash_table_close_t;

int hashtableclose_hash(hash_table_close_t *table, int num);
int hashtableclose_hash(hash_table_close_t *table, int num);
void hashtableclose_clear(hash_table_close_t *table);
int hashtableclose_change_divisor(hash_table_close_t *table, int divisor);
void hashtableclose_add(hash_table_close_t *table, int num, size_t count);
hash_table_close_cell_t hashtableclose_del(hash_table_close_t *table, int num);
hash_table_close_cell_t hashtableclose_find(hash_table_close_t *table, int num);
void hashtableclose_from(hash_table_close_t *table, arr_ints_t *s);
void hashtableclose_print(hash_table_close_t *table);
void hashtableclose_del_ununique(hash_table_close_t *table);
void hashtableclose_rebuild(hash_table_close_t *table);
unsigned long long hashtableclose_del_ununique_time(arr_ints_t *s);
unsigned long long hashtableclose_add_time(arr_ints_t *s);
unsigned long long hashtableclose_del_time(arr_ints_t *s);
unsigned long long hashtableclose_find_time(arr_ints_t *s);
size_t hashtableclose_elem_mem();
size_t hashtableclose_struct_mem();

#endif // #ifndef __HASH_TABLE_CLOSE_H__