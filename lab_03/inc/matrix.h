#ifndef __MATRIX_H__

#define __MATRIX_H__

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "errors_matrix.h"

#include "input.h"
#include "my_time.h"

#define MATRIX_TIME_RUNS 100

#define ROWS_SIZE 500
#define COLS_SIZE 500

typedef struct
{
    size_t size;
    int data[COLS_SIZE];
} vector_col_t;

typedef struct
{
    size_t size;
    int data[ROWS_SIZE];
} vector_row_t;

typedef struct
{
    size_t row_size;
    size_t col_size;
    int data[COLS_SIZE][ROWS_SIZE];
} matrix_t;

int matrix_size_scan(size_t *col_n, size_t *row_m, FILE *stream);
int matrix_scan(matrix_t *matrix, FILE *stream);
void matrix_print(matrix_t *matrix, int formatted, FILE *stream);
int matrix_column_prod(matrix_t *matrix, vector_col_t *v_col, vector_col_t *result);
void matrix_from_column(matrix_t *dst, vector_col_t *src);
void matrix_generate(matrix_t *matrix, int sparsity);
unsigned long long matrix_col_prod_time(void *matrix, vector_col_t *v_col, void *result);

#endif // #ifndef __MATRIX_H__
