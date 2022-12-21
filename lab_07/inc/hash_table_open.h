#ifndef __HASH_TABLE_OPEN_H__

#define __HASH_TABLE_OPEN_H__

#include <stdio.h>
#include <stdlib.h>

#include "errors_hash_table_open.h"

#include "list.h"
#include "my_string.h"
#include "my_time.h"

#define HASH_TABLE_OPEN_DEFAULT_DIVISOR 151

typedef struct
{
    list_t *data;
    int divisor;
} hash_table_open_t;

int hashtableopen_hash(hash_table_open_t *table, char c);
int hashtableopen_init(hash_table_open_t *table);
void hashtableopen_clear(hash_table_open_t *table);
int hashtableopen_change_divisor(hash_table_open_t **table, int divisor);
void hashtableopen_add(hash_table_open_t *table, char c);
hash_table_open_data_t hashtableopen_del(hash_table_open_t *table, char c);
hash_table_open_data_t hashtableopen_find(hash_table_open_t *table, char c);
void hashtableopen_from_string(hash_table_open_t *table, my_string_t s);
void hashtableopen_print(hash_table_open_t *table);
void hashtableopen_del_ununique(hash_table_open_t *table);
unsigned long long hashtableopen_del_ununique_time(my_string_t s);
unsigned long long hashtableopen_add_time(my_string_t s);
unsigned long long hashtableopen_del_time(my_string_t s);
unsigned long long hashtableopen_find_time(my_string_t s);
size_t hashtableopen_elem_mem();
size_t hashtableopen_struct_mem();

#endif // #ifndef __HASH_TABLE_OPEN_H__