#ifndef __ACTIONS_H__

#define __ACTIONS_H__

#include <stdio.h>
#include <stdlib.h>

#include "sparse_matrix.h"

#define ACTIONS_PRINT_WIDTH 100
#define ACTIONS_NUM_PRINT_WIDTH 5

void actions_print();
int actions_handler(int com, sparse_matrix_t *sprs, matrix_t *m);
int exec_input(sparse_matrix_t *sprs, matrix_t *m, int type, FILE *stream);
int exec_output(sparse_matrix_t *sprs, int zeros, int format, FILE *stream);
int exec_prod(sparse_matrix_t *sprs, matrix_t *m, int copy);
int exec_generate(sparse_matrix_t *sprs);
void exec_time_compare(unsigned long long (*method)(void *, vector_col_t *, void *));
void exec_mem_compare(sparse_matrix_t *sprs, matrix_t *m);

#endif // #ifndef __ACTIONS_H__
