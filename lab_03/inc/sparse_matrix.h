#ifndef __SPARSE_MATRIX_H__

#define __SPARSE_MATRIX_H__

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "errors_sparse_matrix.h"

#include "input.h"
#include "matrix.h"
#include "my_time.h"

#define SPARSE_MATRIX_TIME_RUNS 100

#define SIGNIFICANT_SIZE (ROWS_SIZE * COLS_SIZE)

typedef struct
{
    size_t size;
    int data[SIGNIFICANT_SIZE];
} sign_elems_t;

typedef struct
{
    size_t size;
    int data[SIGNIFICANT_SIZE];
} cols_inds_t;

typedef struct 
{
    size_t size;
    int data[ROWS_SIZE];
} row_relation_t;

typedef struct
{
    size_t size;
    row_relation_t rows[COLS_SIZE];
} rows_relations_t;

typedef struct
{
    size_t row_size;
    size_t col_size;
    sign_elems_t values;
    cols_inds_t cols_inds;
    rows_relations_t rows_rels;
} sparse_matrix_t;

int sparsem_matrix_size_scan(size_t *col_n, size_t *row_m, FILE *stream);
int sparsem_values_scan(sign_elems_t *vals, size_t *size, FILE *stream);
int sparsem_cols_inds_scan(cols_inds_t *inds, size_t *size, FILE *stream);
int sparsem_scan(sparse_matrix_t *matrix, FILE *stream);
void sparsem_print_matrix(sparse_matrix_t *matrix, int with_zeros, int formatted, FILE *stream);
int sparsem_column_prod(sparse_matrix_t *matrix, vector_col_t *v_col, sparse_matrix_t *result);
void sparsem_to_matrix(sparse_matrix_t *src, matrix_t *dst);
void sparsem_from_matrix(sparse_matrix_t *dst, matrix_t *src);
unsigned long long sparsem_col_prod_time(void *matrix, vector_col_t *v_col, void *result);

#endif // #ifndef __SPARSE_MATRIX_H__
