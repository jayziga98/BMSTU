#include "../inc/date.h"

int date_sscan(char *s, date_t *date)
{
    size_t i;

    date->day = 0;
    for (i = 0; i < strlen(s) && s[i] != '.'; i++)
        if (isdigit(s[i]))
            date->day = date->day * 10 + (s[i] - '0');
        else
            return EXIT_DAY_INCORRECT_SYMBOLS;

    if (s[i] != '.')
        return EXIT_INCORRECT_DATE;

    date->month = 0;
    for (i++; i < strlen(s) && s[i] != '.'; i++)
        if (isdigit(s[i]))
            date->month = date->month * 10 + (s[i] - '0');
        else
            return EXIT_MONTH_INCORRECT_SYMBOLS;

    if (s[i] != '.')
        return EXIT_INCORRECT_DATE;

    date->year = 0;
    for (i++; i < strlen(s); i++)
        if (isdigit(s[i]))
            date->year = date->year * 10 + (s[i] - '0');
        else
            return EXIT_YEAR_INCORRECT_SYMBOLS;

    return EXIT_SUCCESS;
}

void date_print(date_t *date, int formatted)
{
    char s[PRINT_DATE_WIDTH];
    s[0] = '\0';

    char temp[PRINT_DATE_WIDTH];

    sprintf(temp, "%d.", date->day);
    strcat(s, temp);

    sprintf(temp, "%d.", date->month);
    strcat(s, temp);

    sprintf(temp, "%d", date->year);
    strcat(s, temp);

    if (formatted)
        printf("%-*s|", PRINT_DATE_WIDTH, s);
    else
        printf("%s", s);
}

int year_is_leap(int year)
{
    return (!(year % 4) && (year % 100)) || !(year % 400);
}

int month_prev(int month)
{
    if (month == 1)
        return 12;

    return month - 1;
}

int month_to_days(int month, int year)
{
    int days = 0;
    switch (month)
    {
    case 2:
        days = 28;
        if (year_is_leap(year))
            days = 29;
        break;
    case 1:
    case 3:
    case 5:
    case 7:
    case 8:
    case 10:
    case 12:
        days = 31;
        break;
    case 4:
    case 6:
    case 9:
    case 11:
        days = 30;
        break;
    default:
        break;
    }

    return days;
}

int year_to_days(int year)
{
    if (year_is_leap(year))
        return 366;

    return 365;
}

int date_to_days(date_t *date)
{
    int days = 0;
    for (int i = 1; i < date->month; i++)
        days += month_to_days(i, date->year);
    days += date->day;
    return days;
}

int date_diff_years(date_t *date1, date_t *date2)
{
    return date1->year - date2->year;
}

int date_diff_days(date_t *date1, date_t *date2)
{
    return date_to_days(date1) - date_to_days(date2);
}
