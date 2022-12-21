#include "int_utils.h"

void int_swap(int *num1, int *num2)
{
    int temp = *num1;
    *num1 = *num2;
    *num2 = temp;
}

int int_digits_amount(int num)
{
    int am = 0;
    while (num)
    {
        am++;
        num /= 10;
    }

    return am;
}

int int_reverse(int num)
{
    int rev_num = 0;
    while (num)
    {
        rev_num = rev_num * 10 + num % 10;
        num /= 10;
    }

    return rev_num;
}

int int_max(int num1, int num2)
{
    if (num1 > num2)
        return num1;

    return num2;
}
