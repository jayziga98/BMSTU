#ifndef __BIG_REAL_H__

#define __BIG_REAL_H__

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "int_utils.h"
#include "char_utils.h"
#include "errors_big_real.h"
#include "errors_input.h"

#define MANTISSA_SIZE 30
#define EXPONENT_SIZE 5
#define INPUT_LEN 255
#define BREAL_BASE 10
#define EXPONENT_MAX +99999
#define EXPONENT_MIN -99999

#define CANNOT_EQUALIZE_EXP 1

typedef struct
{
    char m_sign;
    size_t m_size;
    size_t dot_pos;
    char mantissa[MANTISSA_SIZE];
    int exponent;
    int normalized;
} big_real_t;

int breal_scan(big_real_t *num);
size_t breal_del_identseq(big_real_t *num, size_t beg, int digit);
int breal_normalize(big_real_t *num);
void breal_print(big_real_t *num);
void breal_init(big_real_t *num);
size_t breal_last_significant(big_real_t *num);
int breal_sum(big_real_t *num1, big_real_t *num2, big_real_t *result);
void breal_reverse_mantissa(big_real_t *num);

#endif // #ifndef __BIG_REAL_H__
