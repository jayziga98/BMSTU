#ifndef __ACTIONS_H__

#define __ACTIONS_H__

#include <stdio.h>
#include <stdlib.h>

#include "adjacency_matrix.h"

#define COMMAND_NUMBER_LEN 3

void info_print();
int actions_print();
int actions_handler(int com, adjacency_matrix_t *matrix);
void exec_scan(adjacency_matrix_t *matrix);
void exec_print_paths_le(adjacency_matrix_t *matrix);

#endif // #ifndef __ACTIONS_H__