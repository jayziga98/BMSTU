#include "linked_list_queue.h"

int queue_linked_list_empty(void *q)
{
    return (((queue_linked_list_t *)q)->head == NULL);
}

void queue_linked_list_init(void *q)
{
    ((queue_linked_list_t *)q)->head = NULL;
    ((queue_linked_list_t *)q)->tail = NULL;
}

int queue_linked_list_create_node(void *q)
{
    node_t *new = malloc(sizeof(node_t));
    if (new == NULL)
        return EXIT_LINKED_LIST_QUEUE_MEM_ALLOCATE;

    if (queue_linked_list_empty(q))
    {   
        ((queue_linked_list_t *)q)->tail = new;
        ((queue_linked_list_t *)q)->tail->next = NULL;
        ((queue_linked_list_t *)q)->head = ((queue_linked_list_t *)q)->tail;
    }
    else
    {
        ((queue_linked_list_t *)q)->tail->next = new;
        ((queue_linked_list_t *)q)->tail = new;
    }

    return EXIT_SUCCESS;
}

void queue_linked_list_clear(void *q, int addrs)
{
    while (!queue_linked_list_empty(q))
        queue_linked_list_pop(q, NULL, addrs);

    queue_linked_list_init(q);
}

int queue_linked_list_add(void *q, int elem, int addrs)
{
    int rc = 0;

    if ((rc = queue_linked_list_create_node(q)))
        return rc;

    ((queue_linked_list_t *)q)->tail->data = elem;

    if (addrs)
    {
        FILE *f = fopen("addrs.txt", "a+");
        //fprintf(f, "[ADDR: %p -> ELEM: %d]\n", (void *)((queue_linked_list_t *)q)->tail, elem);
        fprintf(f, "%p\n", (void *)((queue_linked_list_t *)q)->tail);
        fclose(f);
    }

    return EXIT_SUCCESS;
}

int queue_linked_list_pop(void *q, int *elem, int addrs)
{
    if (queue_linked_list_empty(q))
    {
        queue_linked_list_clear(q, addrs);
        return EXIT_LINKED_LIST_QUEUE_OVERFLOW;
    }

    node_t *temp = ((queue_linked_list_t *)q)->head;
    if (elem != NULL)
        *elem = temp->data;

    if (addrs)
    {
        FILE *f = fopen("addrs.txt", "a+");
        //fprintf(f, "[ADDR: %p -> ELEM: %d]\n", (void *)((queue_linked_list_t *)q)->head, temp->data);
        fprintf(f, "%p\n", (void *)((queue_linked_list_t *)q)->head);
        fclose(f);
    }

    ((queue_linked_list_t *)q)->head = temp->next;

    free(temp);

    return EXIT_SUCCESS;
}

void queue_linked_list_print(void *q, int addrs)
{
    int elem;
    while (!queue_linked_list_empty(q))
    {
        queue_linked_list_pop(q, &elem, addrs);
        printf("%d ", elem);
    }

    printf("\n");
}

void print_debug_ll(void *q)
{
    printf("\n");
    node_t *cur_node = ((queue_linked_list_t *)q)->head;
    while (cur_node)
        printf("[%d %p]", cur_node->data, (void *)cur_node), cur_node = cur_node->next;

    printf("\n");
}

void queue_linked_list_add_time()
{
    size_t sz[5] = { 1, 10, 100, 500, 1000 };
    size_t n = 5;

    queue_linked_list_t qll;

    queue_linked_list_init(&qll);

    struct timespec beg, end;
    unsigned long long sum = 0;
    unsigned long long sum_del = 0;
    for (size_t i = 0; i < n; i++)
    {
        sum = 0;
        sum_del = 0;
        for (int k = 0; k < TIME_RUNS; k++)
        {
            for (size_t j = 0; j < sz[i]; j++)
            {
                clock_gettime(CLOCK_MONOTONIC_RAW, &beg); 
                queue_linked_list_add(&qll, i, 0);
                clock_gettime(CLOCK_MONOTONIC_RAW, &end); 
                sum += nanoseconds(&beg, &end);
            }

            for (size_t j = 0; j < sz[i]; j++)
            {
                clock_gettime(CLOCK_MONOTONIC_RAW, &beg); 
                queue_linked_list_pop(&qll, NULL, 0);
                clock_gettime(CLOCK_MONOTONIC_RAW, &end); 
                sum_del += nanoseconds(&beg, &end);
            }  
        }

        printf("SZ = %10zu | добавить, ns = %10llu | удалить, ns = %10llu\n", sz[i], sum / TIME_RUNS, sum_del / TIME_RUNS);
    }
}
