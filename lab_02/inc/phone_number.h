#ifndef __PHONE_NUMBER_H__

#define __PHONE_NUMBER_H__

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "errors_phone_number.h"

#define CODE_AREA_SIZE 4
#define NUMBER_SIZE 8
#define PRINT_PHONE_WIDTH 25

typedef struct
{
    char code_country;
    char code_area[CODE_AREA_SIZE];
    char number[NUMBER_SIZE];

} phone_number_t;

int phone_sscan(char *s, phone_number_t *num);
void phone_print(phone_number_t *num, int formatted);
int phone_cmp(phone_number_t *num1, phone_number_t *num2);

#endif // #ifndef __PHONE_NUMBER_H__