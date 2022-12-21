#ifndef __MY_STRING_H__

#define __MY_STRING_H__

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#include "errors_string.h"

#include "my_time.h"
#include "myrandom.h"

#define STR_LEN 50001
#define ALPHABET_SIZE 70

typedef char my_string_t[STR_LEN];

int string_scan(my_string_t s, size_t len, FILE *f);
size_t string_del_ununique(my_string_t s);
unsigned long long string_del_ununique_time(my_string_t s);
void string_print(my_string_t s);
char string_del_rand(my_string_t s);

#endif // #ifndef __MY_STRING_H__