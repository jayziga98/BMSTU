#include "hash_table_close.h"

int hashtableclose_hash(hash_table_close_t *table, int num)
{
    return num % table->divisor;
}

// init hash table with divisor
int hashtableclose_init(hash_table_close_t *table, int divisor)
{
    table->divisor = divisor;
    table->data = malloc(sizeof(hash_table_close_cell_t) * table->divisor);
    if (table->data == NULL)
        return EXIT_HASH_TABLE_CLOSE_MALLOC_ERROR;

    for (int i = 0; i < table->divisor; i++)
        table->data[i].data = 0, table->data[i].cnt = 0;

    return EXIT_SUCCESS;
}

void hashtableclose_clear(hash_table_close_t *table)
{
    if (table->data == NULL)
        return;
    
    free(table->data);
    table->data = NULL;
}

int hashtableclose_change_divisor(hash_table_close_t *table, int divisor)
{
    if (table->data == NULL)
        hashtableclose_init(table, divisor);

    int old_divisor = table->divisor;

    table->divisor = divisor;
    hash_table_close_cell_t *temp = realloc(table->data, sizeof(hash_table_close_cell_t) * table->divisor);
    if (temp == NULL)
        return EXIT_HASH_TABLE_CLOSE_REALLOC_ERROR;

    table->data = temp;

    for (int i = old_divisor; i < table->divisor; i++)
        table->data[i].data = 0, table->data[i].cnt = 0;

    hashtableclose_rebuild(table);

    return EXIT_SUCCESS;
}

void hashtableclose_add(hash_table_close_t *table, int num, size_t count)
{
    int hash = hashtableclose_hash(table, num);
    if (count == 0)
        count = 1;
    hash_table_close_cell_t elem = { .data = num, .cnt = count };
    int is_inserted = 0;
    for (int i = hash; i < table->divisor && !is_inserted && i - hash <= HASH_TABLE_CLOSE_COLLISION_CNT; i++)
        if (table->data[i].cnt > 0 && table->data[i].data == num)
        {
            table->data[i].cnt += count;
            is_inserted = 1;
        }
        else if (table->data[i].cnt < 1)
        {
            table->data[i] = elem;
            is_inserted = 1;
        }

    if (!is_inserted)
    {
        hashtableclose_change_divisor(table, prime_next(table->divisor * 2));
        hashtableclose_add(table, num, count);
    }
}

hash_table_close_cell_t hashtableclose_del(hash_table_close_t *table, int num)
{
    hash_table_close_cell_t elem = { .data = num, .cnt = 1 };

    if (table->data == NULL)
        return elem;

    int hash = hashtableclose_hash(table, num);
    for (int i = hash; i - hash <= HASH_TABLE_CLOSE_COLLISION_CNT  && i < table->divisor; i++)
        if (table->data[i].data == num && table->data[i].cnt != 0)
        {
            elem = table->data[i];
            table->data[i].cnt = 0;
            break;
        }

    return elem;
}

hash_table_close_cell_t hashtableclose_find(hash_table_close_t *table, int num)
{
    hash_table_close_cell_t elem = { .data = 0, .cnt = 0 };

    if (table->data == NULL)
        return elem;

    int hash = hashtableclose_hash(table, num);
    for (int i = hash; i - hash <= HASH_TABLE_CLOSE_COLLISION_CNT  && i < table->divisor; i++)
        if (table->data[i].data == num && table->data[i].cnt != 0)
        {
            elem = table->data[i];
            break;
        }

    return elem;
}

void hashtableclose_from(hash_table_close_t *table, arr_ints_t *s)
{
    hashtableclose_init(table, s->size);

    for (size_t i = 0; i < s->size; i++)
        hashtableclose_add(table, s->data[i], 1);
}

void hashtableclose_print(hash_table_close_t *table)
{
    for (int i = 0; i < table->divisor; i++)
        if (table->data[i].cnt > 0)
        {
            if (table->data[i].cnt > 1)
                printf("[%d: "ANSI_COLOR_GREEN"%d(%d)"ANSI_COLOR_RESET"]", i, table->data[i].data, table->data[i].cnt);
            else
                printf("[%d: %d(%d)]", i, table->data[i].data, table->data[i].cnt);
            printf("\n");
        }
}

void hashtableclose_del_ununique(hash_table_close_t *table)
{
    for (int i = 0; i < table->divisor; i++)
        if (table->data[i].cnt > 1)
            table->data[i].cnt = 0;
}

void hashtableclose_rebuild(hash_table_close_t *table)
{
    hash_table_close_t new;
    new.data = NULL;
    hashtableclose_init(&new, table->divisor);
    for (int i = 0; i < table->divisor; i++)
        if (table->data[i].cnt > 0)
            hashtableclose_add(&new, table->data[i].data, table->data[i].cnt);

    hashtableclose_clear(table);

    table->data = new.data;
}

unsigned long long hashtableclose_del_ununique_time(arr_ints_t *s)
{
    unsigned long long sum = 0;
    for (int i = 0; i < TIME_RUNS; i++)
    {
        struct timespec beg, end;

        hash_table_close_t table;

        hashtableclose_from(&table, s);

        clock_gettime(CLOCK_MONOTONIC_RAW, &beg);   
        hashtableclose_del_ununique(&table);
        clock_gettime(CLOCK_MONOTONIC_RAW, &end);

        hashtableclose_clear(&table);

        sum += nanoseconds(&beg, &end);
    }

    return sum / TIME_RUNS;
}

unsigned long long hashtableclose_add_time(arr_ints_t *s)
{
    unsigned long long sum = 0;

    for (int i = 0; i < TIME_RUNS; i++)
    {
        arr_ints_t copy = *s;

        hash_table_close_t table;
        hashtableclose_init(&table, s->size);

        int cnt = 0;

        unsigned long long avg = 0;
        while (copy.size != 0)
        {
            struct timespec beg, end;

            int c = ints_del_rand(&copy);

            clock_gettime(CLOCK_MONOTONIC_RAW, &beg); 
            hashtableclose_add(&table, c, 1);  
            clock_gettime(CLOCK_MONOTONIC_RAW, &end);

            avg += nanoseconds(&beg, &end);
            cnt++;
        }

        hashtableclose_clear(&table);

        sum += avg / cnt;
    }

    return sum / TIME_RUNS;
}

unsigned long long hashtableclose_del_time(arr_ints_t *s)
{
    unsigned long long sum = 0;

    for (int i = 0; i < TIME_RUNS; i++)
    {
        arr_ints_t copy = *s;

        hash_table_close_t table;

        hashtableclose_from(&table, s);

        int cnt = 0;;

        unsigned long long avg = 0;
        while (copy.size != 0)
        {
            struct timespec beg, end;

            int c = ints_del_rand(&copy);

            clock_gettime(CLOCK_MONOTONIC_RAW, &beg); 
            hashtableclose_del(&table, c); 
            clock_gettime(CLOCK_MONOTONIC_RAW, &end);

            avg += nanoseconds(&beg, &end);
            cnt++;
        }

        hashtableclose_clear(&table);

        sum += avg / cnt;
    }

    return sum / TIME_RUNS;
}

unsigned long long hashtableclose_find_time(arr_ints_t *s)
{
    unsigned long long sum = 0;

    for (int i = 0; i < TIME_RUNS; i++)
    {
        arr_ints_t copy = *s;

        hash_table_close_t table;

        hashtableclose_from(&table, s);

        int cnt = 0;;

        unsigned long long avg = 0;
        while (copy.size != 0)
        {
            struct timespec beg, end;

            int c = ints_del_rand(&copy);

            clock_gettime(CLOCK_MONOTONIC_RAW, &beg); 
            hashtableclose_find(&table, c); 
            clock_gettime(CLOCK_MONOTONIC_RAW, &end);

            avg += nanoseconds(&beg, &end);
            cnt++;
        }

        hashtableclose_clear(&table);

        sum += avg / cnt;
    }

    return sum / TIME_RUNS;
}

size_t hashtableclose_elem_mem()
{
    return sizeof(hash_table_close_cell_t);
}

size_t hashtableclose_struct_mem()
{
    return sizeof(hash_table_close_cell_t) * HASH_TABLE_CLOSE_DEFAULT_DIVISOR + sizeof(hash_table_close_t);
}
