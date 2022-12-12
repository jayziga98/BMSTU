#ifndef __BIG_NUMS_OPERATIONS_H__

#define __BIG_NUMS_OPERATIONS_H__

#include "big_int.h"
#include "big_real.h"

#define TEMP_SIZE 60
#define BNUMSOP_BASE 10

typedef struct 
{
    size_t size;
    char data[TEMP_SIZE];
} temp_t;

int bnumsop_multiply(big_real_t *num1, big_int_t *num2, big_real_t *result);
void bnumsop_copy(temp_t *src, big_real_t *dst);
int bnumsop_round(temp_t *src, size_t rank);
void temp_reverse(temp_t *temp);
int temp_sum(temp_t *temp1, temp_t *temp2, temp_t *result);
void temp_print(temp_t *temp);

#endif // #ifndef __BIG_NUMS_OPERATIONS_H__
