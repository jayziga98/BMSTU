#include <stdio.h>
#include <stdlib.h>
#include "big_real.h"
#include "big_int.h"
#include "int_utils.h"
#include "beauty_print.h"
#include "big_nums_operations.h"

#define TABLE_LEFT_SPACE 24
#define TABLE_FULL_SIZE 67

void error_handler(int rc);

int main()
{
    int rc = 0;

    printf("\t Программа выполняет умножение действительного числа на целое. Результат - действительное число в нормализованном виде.\n\n");
    printf("Первый множитель - действительное число. Вводится в формате [+-]m[.[n]][Ee][+-]k\n");
    printf("m - целая часть мантиссы | n - дробная часть мантиссы | (m + n) максимум 30 символов | k - порядок (от -99999 до +99999)\n");
    printf("Второй множитель - целое число. Вводится в формате [+-]d\n");
    printf("d - цифры целого числа (максимум 30 символов)\n");
    printf("Квадратные скобки обозначают возможность отсутствия той или иной части числа\n");
    printf("Прим ввода действительного числа: 1.E1 | +1014.E15 | -.E15\n");

    beautyp_nsyms(TABLE_FULL_SIZE, '_');
    printf("\n\t\t\t|  ");
    int a[SEGMENTS_SIZE] = { MANTISSA_SIZE, EXPONENT_SIZE };
    int ruller_size = beautyp_ruller(a, 2);
    printf("  |\n");
    beautyp_nsyms(TABLE_LEFT_SPACE, '_');
    printf("|");
    beautyp_nsyms(ruller_size + 7, '_');
    printf("|\n");

    printf("Введите первый множитель|   ");
    big_real_t num1;
    if ((rc = breal_scan(&num1)))
    {
        error_handler(rc);
        return rc;
    }
    printf("Введите второй множитель|   ");
    big_int_t num2;
    if ((rc = bint_scan(&num2)))
    {
        error_handler(rc);
        return rc;
    }
    breal_normalize(&num1);

    beautyp_nsyms(TABLE_LEFT_SPACE, '_');
    printf("|___");
    beautyp_nsyms(ruller_size + 4, '_');
    printf("|\n");
    printf("Первый множитель\t|  ");

    breal_print(&num1);

    printf("Операция\t\t|*");
    beautyp_nsyms(ruller_size + 6, ' ');
    printf("|\n");
    
    printf("Второй множитель\t|  ");
    bint_print(&num2);

    beautyp_nsyms(TABLE_LEFT_SPACE, '-');
    printf("|");
    beautyp_nsyms(TABLE_FULL_SIZE - TABLE_LEFT_SPACE - 1, '-');
    printf("|\n");

    big_real_t result;
    if ((rc = bnumsop_multiply(&num1, &num2, &result)) || (rc = breal_normalize(&result)))
    {
        error_handler(rc);
        return rc;
    }
    breal_normalize(&result);

    printf("Результат\t\t|  ");

    breal_print(&result);

    beautyp_nsyms(TABLE_FULL_SIZE, '_');
    printf("|\n");

    return EXIT_SUCCESS;
}

void error_handler(int rc)
{
    switch (rc)
    {
        case EXIT_EXPONENT_OVERFLOW:
            printf("Ошибка: Порядок переполнился!");
            break;
        case EXIT_MANTISSA_OVERFLOW:
            printf("Ошибка: Мантисса переполнилась!");
            break;
        case EXIT_BIG_INT_OVERFLOW:
            printf("Ошибка: Слишком большое целое число!");
            break;
        case EXIT_EMPTY_INPUT:
            printf("Ошибка: Вы ничего не ввели!");
            break;
        case EXIT_NOT_INPUT_BIG_REAL:
            printf("Ошибка: Вы не ввели первое число!");
            break;
        case EXIT_NOT_INPUT_BIG_INT:
            printf("Ошибка: Вы не ввели второе число!");
            break;
        case EXIT_INPUT_OVERFLOW:
            printf("Ошибка: Вы ввели слишком много!");
            break;
        case EXIT_INCORRECT_SYMBOLS:
            printf("Ошибка: Вы ввели недопустимые символы!");
            break;
        default:
            printf("Ошибка: Неизвестная ошибка!");
    }
}
