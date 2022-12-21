#include "adjacency_matrix.h"

void adjacency_matrix_init(adjacency_matrix_t *matrix)
{
    matrix->data = NULL;
    matrix->size = 0;
}

void adjacency_matrix_free(adjacency_matrix_t *matrix)
{
    for (size_t i = 0; i < matrix->size; i++)
        if (matrix->data[i])
            free(matrix->data[i]);

    free(matrix->data);
    adjacency_matrix_init(matrix);
}

int adjacency_matrix_create(adjacency_matrix_t *matrix, size_t vertex_amount)
{
    matrix->size = vertex_amount;

    matrix->data = calloc(matrix->size, sizeof(int *));
    if (!matrix->data)
        return EXIT_ALLOCATING_ROW_PTRS_MEMORY_ERRORY;

    for (size_t i = 0; i < matrix->size; i++)
    {
        int *row = malloc(matrix->size * sizeof(int));
        if (!row)
        {
            adjacency_matrix_free(matrix);
            return EXIT_ALOCATING_ROW_MEMORY_ERRROR;
        }

        matrix->data[i] = row;
    }

    return EXIT_SUCCESS;
}

void adjacency_matrix_fill_max(adjacency_matrix_t *matrix)
{
    for (size_t i = 0; i < matrix->size; i++)
        for (size_t j = 0; j < matrix->size; j++)
            matrix->data[i][j] = MAX_COST + 1;
}

void adjacency_matrix_add(adjacency_matrix_t *matrix, int from, int to, int cost)
{
    if (from > -1 && (size_t)from < matrix->size && to > -1 && (size_t)to < matrix->size && cost <= MAX_COST && cost >= MIN_COST)
        matrix->data[from][to] = cost;
}

int *adjacency_matrix_shortest_paths(adjacency_matrix_t *matrix, int from)
{
    int *used = calloc(matrix->size, sizeof(int));
    int *paths = malloc(matrix->size * sizeof(int));

    for (size_t i = 0; i < matrix->size; i++)
        paths[i] = MAX_PATH_COST;

    paths[from] = 0;

    for (size_t i = 0; i < matrix->size; i++)
    {
        int v = -1;
        for (size_t j = 0; j < matrix->size; j++)
            if (!used[j] && (v == -1 || paths[v] > paths[j]))
                v = j;

        if (v == -1 || paths[v] == MAX_PATH_COST)
            break;

        used[v] = 1;

        for (size_t to = 0; to < matrix->size; to++)
            if (matrix->data[v][to] <= MAX_COST && paths[to] > paths[v] + matrix->data[v][to])
                paths[to] = paths[v] + matrix->data[v][to];
    }

    free(used);

    return paths;
}

void adjacency_matrix_paths_le_to_dot(adjacency_matrix_t *matrix, int from, int max_cost)
{
    FILE *f = fopen("graph.gv", "w+");

    fprintf(f, "digraph %s {\n", "Граф");

    int *shortest_paths = NULL;
    shortest_paths = adjacency_matrix_shortest_paths(matrix, from);

    for (size_t i = 0; i < matrix->size; i++)
        for (size_t j = 0; j < matrix->size; j++)
            if (matrix->data[i][j] != MAX_COST + 1)
                fprintf(f, "%zu -> %zu [label=%d];\n", i + 1, j + 1, matrix->data[i][j]);

    for (size_t i = 0; i < matrix->size; i++)
        if (i == (size_t)from)
            fprintf(f, "%zu [label=\"%zu старт\",shape=circle,color=green,style=filled];\n", i + 1, i + 1);
        else if (shortest_paths[i] <= max_cost)
            fprintf(f, "%zu [label=\"%zu путь=%d\",shape=circle,color=lightblue,style=filled];\n", i + 1, i + 1, shortest_paths[i]);
        else if (shortest_paths[i] == MAX_PATH_COST)
            fprintf(f, "%zu [label=\"%zu путь=inf\",shape=circle,color=red,style=filled];\n", i + 1, i + 1);
        else
            fprintf(f, "%zu [label=\"%zu путь=%d\",shape=circle];\n", i + 1, i + 1, shortest_paths[i]);

    fprintf(f, "}\n");

    fclose(f);
}

void adjacency_matrix_to_dot(adjacency_matrix_t *matrix)
{
    FILE *f = fopen("graph.gv", "w+");

    fprintf(f, "digraph %s {\n", "Граф");

    for (size_t i = 0; i < matrix->size; i++)
        for (size_t j = 0; j < matrix->size; j++)
            if (matrix->data[i][j] != MAX_COST + 1)
                fprintf(f, "%zu -> %zu [label=%d];\n", i + 1, j + 1, matrix->data[i][j]);

    fprintf(f, "}\n");

    fclose(f);
}
