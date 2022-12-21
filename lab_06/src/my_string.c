#include "my_string.h"

int string_scan(my_string_t s, size_t len, FILE *f)
{
    if (fgets(s, len, f) == NULL || s[strlen(s) - 1] != '\n')
        return EXIT_STRING_SCAN_ERROR;

    s[strlen(s) - 1] = '\0';

    if (s[0] == '\0')
        return EXIT_STRING_EMPTY_ERROR;

    return EXIT_SUCCESS;
}

size_t string_del_ununique(my_string_t s)
{
    int cnt[ALPHABET_SIZE];
    for (size_t i = 0; i < ALPHABET_SIZE; i++)
        cnt[i] = 0;

    for (size_t i = 0; s[i] != '\0'; i++)
        cnt[s[i] - 'A']++;

    size_t new_size = 0;
    for (size_t i = 0; s[i] != '\0'; i++)
        if (cnt[s[i] - 'A'] == 1)
        {
            new_size++;
            s[new_size - 1] = s[i];
        }

    s[new_size] = '\0';

    return new_size;
}

unsigned long long string_del_ununique_time(my_string_t s)
{
    unsigned long long sum = 0;

    for (int i = 0; i < TIME_RUNS; i++)
    {
        struct timespec beg, end;

        my_string_t copy;
        strcpy(copy, s);

        clock_gettime(CLOCK_MONOTONIC_RAW, &beg);   
        string_del_ununique(copy);
        clock_gettime(CLOCK_MONOTONIC_RAW, &end);

        sum += nanoseconds(&beg, &end);
    }

    return sum / TIME_RUNS;
}

char string_del_rand(my_string_t s)
{
    size_t ind_del = rand_size_from(0, strlen(s));
    char sym = s[ind_del];

    size_t new_size = 0;
    for (size_t i = 0; i < strlen(s); i++)
        if (i != ind_del)
        {
            new_size++;
            s[new_size - 1] = s[i];
        }

    s[new_size] = '\0';

    return sym;
}

void string_print(my_string_t s)
{
    for (size_t i = 0; s[i] != '\0'; i++)
        printf("%c ", s[i]);

    printf("\n");
}
