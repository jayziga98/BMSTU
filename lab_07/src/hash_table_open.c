#include "hash_table_open.h"

int hashtableopen_hash(hash_table_open_t *table, char c)
{
    return c % table->divisor;
}

// init hash table with default divisor
int hashtableopen_init(hash_table_open_t *table)
{
    table->divisor = HASH_TABLE_OPEN_DEFAULT_DIVISOR;
    table->data = malloc(sizeof(list_t) * table->divisor);
    if (table->data == NULL)
        return EXIT_HASH_TABLE_OPEN_MALLOC_ERROR;

    for (int i = 0; i < table->divisor; i++)
        list_init(&(table->data[i]));

    return EXIT_SUCCESS;
}

void hashtableopen_clear(hash_table_open_t *table)
{
    if (table->data == NULL)
        return;

    for (int i = 0; i < table->divisor; i++)
        list_clear(&(table->data[i]));
    
    free(table->data);
    table->data = NULL;
}

int hashtableopen_change_divisor(hash_table_open_t **table, int divisor)
{
    if ((*table)->data == NULL)
        hashtableopen_init(*table);

    (*table)->divisor = divisor;
    list_t *temp = realloc((*table)->data, sizeof(list_t) * (*table)->divisor);
    if (temp == NULL)
        return EXIT_HASH_TABLE_OPEN_REALLOC_ERROR;

    (*table)->data = temp;

    // hashtableopen_rebuild(table);

    return EXIT_SUCCESS;
}

void hashtableopen_add(hash_table_open_t *table, char c)
{
    int hash = hashtableopen_hash(table, c);
    hash_table_open_data_t elem = { .letter = c, .count = 1 };
    list_add_by(&(table->data[hash]), &elem);
}

hash_table_open_data_t hashtableopen_del(hash_table_open_t *table, char c)
{
    hash_table_open_data_t elem = { .letter = c, .count = 1 };

    if (table->data == NULL)
        return elem;

    int hash = hashtableopen_hash(table, c);
    list_del_by(&(table->data[hash]), &elem);

    return elem;
}

hash_table_open_data_t hashtableopen_find(hash_table_open_t *table, char c)
{
    hash_table_open_data_t elem = { .letter = '\0', .count = 0 };

    if (table->data == NULL)
        return elem;

    int hash = hashtableopen_hash(table, c);
    elem.count = list_count(&(table->data[hash]), c);
    elem.letter = c;

    return elem;
}

void hashtableopen_from_string(hash_table_open_t *table, my_string_t s)
{
    hashtableopen_init(table);

    for (size_t i = 0; s[i] != '\0'; i++)
        hashtableopen_add(table, s[i]);
}

void hashtableopen_print(hash_table_open_t *table)
{
    for (int i = 0; i < table->divisor; i++)
        if (!list_empty(&(table->data[i])))
        {
            printf("[%d: ", i);
            list_print(&(table->data[i]), '|', ']');
            printf("\n");
        }
}

void hashtableopen_del_ununique(hash_table_open_t *table)
{
    for (int i = 0; i < table->divisor; i++)
    {
        list_del_ununique(&(table->data[i]));
        if (list_empty(&(table->data[i])))
            list_init(&(table->data[i]));
    }
}

// void hashtableopen_rebuild(hash_table_open_t *table)
// {
//     *table = new_table;
// }

unsigned long long hashtableopen_del_ununique_time(my_string_t s)
{
    unsigned long long sum = 0;

    for (int i = 0; i < TIME_RUNS; i++)
    {
        struct timespec beg, end;

        hash_table_open_t table;
        hashtableopen_init(&table);

        hashtableopen_from_string(&table, s);

        clock_gettime(CLOCK_MONOTONIC_RAW, &beg);   
        hashtableopen_del_ununique(&table);
        clock_gettime(CLOCK_MONOTONIC_RAW, &end);

        hashtableopen_clear(&table);

        sum += nanoseconds(&beg, &end);
    }

    return sum / TIME_RUNS;
}

unsigned long long hashtableopen_add_time(my_string_t s)
{
    unsigned long long sum = 0;

    for (int i = 0; i < TIME_RUNS; i++)
    {
        my_string_t copy;
        strcpy(copy, s);

        hash_table_open_t table;
        hashtableopen_init(&table);

        int cnt = 0;

        unsigned long long avg = 0;
        while (copy[0] != '\0')
        {
            struct timespec beg, end;

            char c = string_del_rand(copy);

            clock_gettime(CLOCK_MONOTONIC_RAW, &beg); 
            hashtableopen_add(&table, c);  
            clock_gettime(CLOCK_MONOTONIC_RAW, &end);

            avg += nanoseconds(&beg, &end);
            cnt++;
        }

        hashtableopen_clear(&table);

        sum += avg / cnt;
    }

    return sum / TIME_RUNS;
}

unsigned long long hashtableopen_del_time(my_string_t s)
{
    unsigned long long sum = 0;

    for (int i = 0; i < TIME_RUNS; i++)
    {
        my_string_t copy;
        strcpy(copy, s);

        hash_table_open_t table;
        hashtableopen_init(&table);

        hashtableopen_from_string(&table, s);

        int cnt = 0;;

        unsigned long long avg = 0;
        while (copy[0] != '\0')
        {
            struct timespec beg, end;

            char c = string_del_rand(copy);

            clock_gettime(CLOCK_MONOTONIC_RAW, &beg); 
            hashtableopen_del(&table, c); 
            clock_gettime(CLOCK_MONOTONIC_RAW, &end);

            avg += nanoseconds(&beg, &end);
            cnt++;
        }

        hashtableopen_clear(&table);

        sum += avg / cnt;
    }

    return sum / TIME_RUNS;
}

unsigned long long hashtableopen_find_time(my_string_t s)
{
    unsigned long long sum = 0;

    for (int i = 0; i < TIME_RUNS; i++)
    {
        my_string_t copy;
        strcpy(copy, s);

        hash_table_open_t table;
        hashtableopen_init(&table);

        hashtableopen_from_string(&table, s);

        int cnt = 0;;

        unsigned long long avg = 0;
        while (copy[0] != '\0')
        {
            struct timespec beg, end;

            char c = string_del_rand(copy);

            clock_gettime(CLOCK_MONOTONIC_RAW, &beg); 
            hashtableopen_find(&table, c); 
            clock_gettime(CLOCK_MONOTONIC_RAW, &end);

            avg += nanoseconds(&beg, &end);
            cnt++;
        }

        hashtableopen_clear(&table);

        sum += avg / cnt;
    }

    return sum / TIME_RUNS;
}

size_t hashtableopen_elem_mem()
{
    list_t list = { .head = NULL, .size = 1 };
    return list_mem(&list);
}

size_t hashtableopen_struct_mem()
{
    return sizeof(list_t) * HASH_TABLE_OPEN_DEFAULT_DIVISOR + sizeof(hash_table_open_t);
}
