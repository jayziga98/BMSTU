#ifndef __ADJACENCY_MATRIX_H__

#define __ADJACENCY_MATRIX_H__

#include <stdio.h>
#include <stdlib.h>

#include "errors_adjacency_matrix.h"

#define MIN_COST 0
#define MAX_COST 1000
#define MAX_SIZE 1000
#define MAX_PATH_COST MAX_COST * MAX_SIZE

typedef struct
{
    size_t size;
    int **data;
} adjacency_matrix_t;

void adjacency_matrix_init(adjacency_matrix_t *matrix);
void adjacency_matrix_free(adjacency_matrix_t *matrix);
int adjacency_matrix_create(adjacency_matrix_t *matrix, size_t vertex_amount);
void adjacency_matrix_fill_max(adjacency_matrix_t *matrix);
void adjacency_matrix_add(adjacency_matrix_t *matrix, int from, int to, int cost);
int *adjacency_matrix_shortest_paths(adjacency_matrix_t *matrix, int from);
void adjacency_matrix_paths_le_to_dot(adjacency_matrix_t *matrix, int from, int max_cost);
void adjacency_matrix_to_dot(adjacency_matrix_t *matrix);

#endif // #ifndef __ADJACENCY_MATRIX_H__