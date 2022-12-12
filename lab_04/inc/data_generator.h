#ifndef __DATA_GENERATOR_H__

#define __DATA_GENERATOR_H__

#include <stdio.h>
#include <stdlib.h>

#define DATA_MAX_ARRAY_SIZE 100

void fill_arr_ascending(int a[DATA_MAX_ARRAY_SIZE], size_t n);
void fill_arr_descending(int a[DATA_MAX_ARRAY_SIZE], size_t n);
void fill_arr_period(int a[DATA_MAX_ARRAY_SIZE], size_t n, int period);
void fill_arr_rand(int a[DATA_MAX_ARRAY_SIZE], size_t n);

#endif // #ifndef __DATA_GENERATOR_H__
