#include "queue.h"

int queuestd_empty(void *q)
{
    return (((queue_std_t *)q)->tail == ((queue_std_t *)q)->head);
}

void queuestd_init(void *q)
{
    ((queue_std_t *)q)->allocated = 0;
    ((queue_std_t *)q)->head = NULL;
    ((queue_std_t *)q)->tail = NULL;
    ((queue_std_t *)q)->data = NULL;
    ((queue_std_t *)q)->begin = NULL;
    ((queue_std_t *)q)->end = NULL;
}

int queuestd_create(void *q, size_t n_elems)
{
    queuestd_init(q);

    ((queue_std_t *)q)->data = malloc(n_elems * sizeof(int));
    if (((queue_std_t *)q)->data == NULL)
        return EXIT_QUEUE_MEM_ALLOCATE;

    ((queue_std_t *)q)->begin = ((queue_std_t *)q)->data;
    ((queue_std_t *)q)->allocated = n_elems;
    ((queue_std_t *)q)->end = ((queue_std_t *)q)->begin + ((queue_std_t *)q)->allocated;

    ((queue_std_t *)q)->head = NULL;
    ((queue_std_t *)q)->tail = ((queue_std_t *)q)->begin + 1;

    return EXIT_SUCCESS;
}

int queuestd_fill_order(void *q, size_t n_elems, int addrs)
{
    int rc = 0;
   
    if ((rc = queuestd_create(q, n_elems)))
        return rc;

    int num = 1;
    for (size_t i = 0; i < n_elems; i++, num++)
        if ((rc = queuestd_add(q, num, addrs)))
            return rc;

    return EXIT_SUCCESS;
}

void queuestd_clear(void *q, int addrs)
{
    if(addrs)
        addrs++;
        
    free(((queue_std_t *)q)->data);
    queuestd_init(q);
}

void queuestd_tail_rshift(void *q)
{
    if(((queue_std_t *)q)->tail == ((queue_std_t *)q)->end)
        ((queue_std_t *)q)->tail = ((queue_std_t *)q)->begin;
    else
    {
        ((queue_std_t *)q)->tail++;

        if(((queue_std_t *)q)->tail == ((queue_std_t *)q)->end)
            ((queue_std_t *)q)->tail = ((queue_std_t *)q)->begin;
    }
}

void queuestd_head_rshift(void *q)
{
    if(((queue_std_t *)q)->head == ((queue_std_t *)q)->end)
        ((queue_std_t *)q)->head = ((queue_std_t *)q)->begin;
    else
    {
        ((queue_std_t *)q)->head++;

        if(((queue_std_t *)q)->head == ((queue_std_t *)q)->end)
            ((queue_std_t *)q)->head = ((queue_std_t *)q)->begin;
    }
}

int queuestd_add(void *q, int elem, int addrs)
{
    if (!((queue_std_t *)q)->tail)
    {
        queuestd_clear(q, addrs);
        return EXIT_QUEUE_OVERFLOW;
    }

    *(((queue_std_t *)q)->tail) = elem;
    if (((queue_std_t *)q)->head == NULL)
        ((queue_std_t *)q)->head = ((queue_std_t *)q)->tail;

    if (addrs)
            printf("[ADDR: %p -> ELEM: %d]\n", (void *)(((queue_std_t *)q)->tail), elem);

    queuestd_tail_rshift(q);

    return EXIT_SUCCESS;
}

void print_debug(void *q)
{
    //printf("HEAD: %p | TAIL: %p\n", (void *)((queue_std_t *)q)->head, (void *)((queue_std_t *)q)->tail);

    printf("\n");

    for (int *i = ((queue_std_t *)q)->begin; i < ((queue_std_t *)q)->end; i++)
    { 
        if (((queue_std_t *)q)->head == i)
            printf("[HEAD ");
        if (((queue_std_t *)q)->tail == i)
            printf("[TAIL ");
        printf("%d ", *i);
    }

    printf("\n");

    for (int *i = ((queue_std_t *)q)->begin; i < ((queue_std_t *)q)->end; i++)
    { 
        if (((queue_std_t *)q)->head == i)
            printf("[HEAD ");
        if (((queue_std_t *)q)->tail == i)
            printf("[TAIL ");
        printf("%p ", (void *)i);
    }

    printf("\n");
}

int queuestd_pop(void *q, int *elem, int addrs)
{
    if (((queue_std_t *)q)->head && !queuestd_empty(q))
    {
        if (elem != NULL)
            *elem = *(((queue_std_t *)q)->head);
        if (addrs)
            printf("[ADDR: %p -> ELEM: %d]\n", (void *)(((queue_std_t *)q)->head), *(((queue_std_t *)q)->head));
        queuestd_head_rshift(q);
    }

    return EXIT_SUCCESS;
}

void queuestd_print(void *q, int addrs)
{
    int flag = 0;
    int elem = -1;
    while(!queuestd_pop(q, &elem, addrs))
    {
        printf("%d ", elem);
        flag = 1;
    }

    if (flag)
        printf("%d ", elem);

    printf("\n");
}

void queuestd_add_time()
{
    size_t sz[5] = { 1, 10, 100, 500, 1000 };
    size_t n = 5;

    queue_std_t q;

    queuestd_init(&q);
    queuestd_create(&q, sz[n - 1]);

    struct timespec beg, end;
    unsigned long long sum = 0, sum_del = 0;
    for (size_t i = 0; i < n; i++)
    {
        sum = 0;
        sum_del = 0;
        for (int k = 0; k < TIME_RUNS; k++)
        {
            for (size_t j = 0; j < sz[i]; j++)
            {
                clock_gettime(CLOCK_MONOTONIC_RAW, &beg); 
                queuestd_add(&q, i, 0);
                clock_gettime(CLOCK_MONOTONIC_RAW, &end); 
                sum += nanoseconds(&beg, &end);
            }

            for (size_t j = 0; j < sz[i]; j++)
            {
                clock_gettime(CLOCK_MONOTONIC_RAW, &beg); 
                queuestd_pop(&q, NULL, 0);
                clock_gettime(CLOCK_MONOTONIC_RAW, &end); 
                sum_del += nanoseconds(&beg, &end);
            }  
        }

        printf("SZ = %10zu | добавить, ns = %10llu | удалить, ns = %10llu\n", sz[i], sum / TIME_RUNS, sum_del / TIME_RUNS);
    }
}
