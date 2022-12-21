#include "data_generator.h"

void fill_arr_ascending(int a[DATA_MAX_ARRAY_SIZE], size_t n)
{
    for (size_t i = 1; i <= n; i++)
        a[i] = i;
}

void fill_arr_descending(int a[DATA_MAX_ARRAY_SIZE], size_t n)
{
    for (size_t i = 0; i <= n; i++)
        a[i] = n - i;
}

void fill_arr_period(int a[DATA_MAX_ARRAY_SIZE], size_t n, int period)
{
    for (size_t i = 1; i <= n; i++)
        a[i] = i % period;
}

void fill_arr_rand(int a[DATA_MAX_ARRAY_SIZE], size_t n)
{
    for (size_t i = 0; i <= n; i++)
        a[i] = rand();
}
