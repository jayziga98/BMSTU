#ifndef __INPUT_H__

#define __INPUT_H__

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "errors_input.h"

#define BUFFER_LEN 400

#define PRINT_INT_WIDTH 9

int input_str(FILE *stream, char str[BUFFER_LEN]);
int input_ints(FILE *stream, int data[], size_t *size, size_t size_max, char *delim);
int input_size(FILE *stream, size_t *data);
int input_int(FILE *stream, int *data);

#endif // #ifndef __INPUT_H__
