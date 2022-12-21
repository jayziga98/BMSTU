#ifndef __BIG_INT_H__

#define __BIG_INT_H__

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "int_utils.h"
#include "char_utils.h"
#include "errors_input.h"
#include "errors_big_int.h"

#define BIG_INT_SIZE 30
#define SIGNS 2
#define INPUT_LEN 255
#define BINT_BASE 10

typedef struct
{
    char sign;
    size_t size;
    char digits[BIG_INT_SIZE];
} big_int_t;

int bint_scan(big_int_t *num);
void bint_print(big_int_t *num);

#endif // #ifndef __BIG_INT_H__
