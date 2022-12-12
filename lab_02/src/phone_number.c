#include "../inc/phone_number.h"

int phone_sscan(char *s, phone_number_t *num)
{
    size_t i;

    num->code_country = 'A';
    for (i = 0; i < strlen(s); i++)
        if (isdigit(s[i]))
        {
            num->code_country = s[i];
            i++;
            break;
        }

    int flag = 0;
    size_t size;
    for (size = 0; i < strlen(s) && size < CODE_AREA_SIZE - 1; i++)
        if (isdigit(s[i]))
        {
            size++;
            num->code_area[size - 1] = s[i];
        }
        else
        {
            if (flag)
                break;
            flag = 1;
        }
    num->code_area[size] = '\0';

    flag = 0;
    for (size = 0; i < strlen(s) && size < NUMBER_SIZE - 1; i++)
        if (isdigit(s[i]))
        {
            size++;
            num->number[size - 1] = s[i];
        }
        else
        {
            if (flag)
                break;
            flag = 1;
        }
    num->number[size] = '\0';

    if (num->code_country < '0' || num->code_country > '9' || strlen(num->code_area) != CODE_AREA_SIZE - 1 || strlen(num->number) != NUMBER_SIZE - 1)
        return EXIT_INCORRECT_PHONE;

    return EXIT_SUCCESS;
}

void phone_print(phone_number_t *num, int formatted)
{
    if (formatted)
    {
        char s[PRINT_PHONE_WIDTH];
        s[0] = '+';
        s[1] = num->code_country;
        s[3] = '\0';
        strcat(s, num->code_area);
        strcat(s, num->number);

        printf("%-*s|", PRINT_PHONE_WIDTH, s);
    }
    else
    {
        char s[PRINT_PHONE_WIDTH];
        s[0] = num->code_country;
        s[1] = '\0';
        strcat(s, num->code_area);
        strcat(s, num->number);

        printf("%s", s);
    }
}

int phone_cmp(phone_number_t *num1, phone_number_t *num2)
{
    int country_cmp = (num1->code_country - num2->code_country);
    int area_cmp = strcmp(num1->code_area, num2->code_area);
    int number_cmp = strcmp(num1->number, num2->number);

    if (country_cmp)
        return country_cmp;
    else if (area_cmp)
        return area_cmp;
    
    return number_cmp;
}
