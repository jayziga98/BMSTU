#include "arr_ints.h"

int ints_scan(arr_ints_t *s, size_t len, FILE *f)
{
    s->size = len;
    for (size_t i = 0; i < len; i++)
        if (fscanf(f, "%d", &(s->data[i])) != 1)
        {
            s->size = i;
            return EXIT_ARR_INTS_SCAN_ERROR;
        }

    s->size = len;

    return EXIT_SUCCESS;
}

int ints_del_rand(arr_ints_t *s)
{
    size_t ind_del = rand_size_from(0, s->size);
    int sym = s->data[ind_del];

    size_t new_size = 0;
    for (size_t i = 0; i < s->size; i++)
        if (i != ind_del)
        {
            new_size++;
            s->data[new_size - 1] = s->data[i];
        }

    s->size = new_size;

    return sym;
}

void ints_print(arr_ints_t *s)
{
    for (size_t i = 0; i < s->size; i++)
        printf("%d ", s->data[i]);

    printf("\n");
}
