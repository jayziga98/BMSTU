#include "beauty_print.h"

void beautyp_nsyms(int n, char c)
{
    for (int i = 0; i < n; i++)
        printf("%c", c);
}

// Печатает линейку формата [0123456789012...|01234...|0123456...]
// массив сегментов содержит размеры каждого сегмента линейки
// Переводит курсор на новую строку
int beautyp_ruller(int segments[SEGMENTS_SIZE], size_t seg_n)
{
    int size = 0;
    printf("[");
    for (size_t i = 0; i < seg_n; i++)
    {
        int val = 0;
        for (int j = 0; j < segments[i]; j++, val++, val %= 10, size++)
            printf("%d", val);

        if (i < seg_n - 1)
            printf("|");
    }

    printf("]");

    return size;
}
