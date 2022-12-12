#ifndef __ARR_INTS_H__

#define __ARR_INTS_H__

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#include "errors_arr_ints.h"

#include "my_time.h"
#include "myrandom.h"

#define ARR_SIZE 50001

typedef struct {
    size_t size;
    int data[ARR_SIZE];
} arr_ints_t;

int ints_scan(arr_ints_t *s, size_t len, FILE *f);
void ints_print(arr_ints_t *s);
int ints_del_rand(arr_ints_t *s);

#endif // #ifndef __ARR_INTS_H__