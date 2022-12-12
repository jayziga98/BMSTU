#ifndef __DATE_H__

#define __DATE_H__

#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>
#include "errors_date.h"

#define PRINT_DATE_WIDTH 50

typedef struct
{
    int day;
    int month;
    int year;
} date_t;

int date_sscan(char *s, date_t *date);
void date_print(date_t *date, int formatted);
int year_is_leap(int year);
int month_to_prev(int month);
int month_to_days(int month, int year);
int year_to_days(int year);
int date_to_days(date_t *date);
int date_diff_years(date_t *date1, date_t *date2);
int date_diff_days(date_t *date1, date_t *date2);

#endif // #ifndef __DATE_H__