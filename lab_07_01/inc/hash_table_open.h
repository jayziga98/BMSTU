#ifndef __HASH_TABLE_OPEN_H__

#define __HASH_TABLE_OPEN_H__

#include <stdio.h>
#include <stdlib.h>

#include "errors_hash_table_open.h"

#include "list.h"
#include "arr_ints.h"
#include "my_time.h"
#include "prime.h"

#define HASH_TABLE_OPEN_DEFAULT_DIVISOR 151
#define HASH_TABLE_OPEN_COLLISION_CNT 4

typedef struct
{
    list_t *data;
    int divisor;
} hash_table_open_t;

int hashtableopen_hash(hash_table_open_t *table, int c);
int hashtableopen_init(hash_table_open_t *table, int divisor);
void hashtableopen_clear(hash_table_open_t *table);
int hashtableopen_change_divisor(hash_table_open_t *table, int divisor);
void hashtableopen_add(hash_table_open_t *table, int c, size_t count);
hash_table_open_data_t hashtableopen_del(hash_table_open_t *table, int c);
hash_table_open_data_t hashtableopen_find(hash_table_open_t *table, int c);
void hashtableopen_from(hash_table_open_t *table, arr_ints_t *s);
void hashtableopen_print(hash_table_open_t *table);
void hashtableopen_del_ununique(hash_table_open_t *table);
void hashtableopen_rebuild(hash_table_open_t *table);
unsigned long long hashtableopen_del_ununique_time(arr_ints_t *s);
unsigned long long hashtableopen_add_time(arr_ints_t *s);
unsigned long long hashtableopen_del_time(arr_ints_t *s);
unsigned long long hashtableopen_find_time(arr_ints_t *s);
size_t hashtableopen_elem_mem();
size_t hashtableopen_struct_mem();

#endif // #ifndef __HASH_TABLE_OPEN_H__