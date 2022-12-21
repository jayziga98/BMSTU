#include "linked_list_stack.h"

void linkedstack_addrs_add(addrs *freed_addrs, void *addr)
{
    if (freed_addrs->size < LINKED_LIST_STACK_FREED_ADDRS_SIZE)
    {
        int flag = 0;
        for (size_t i = 0; !flag && i < freed_addrs->size; i++)
            if (freed_addrs->data[i] == addr)
                flag = 1;

        if (!flag)
        {
            freed_addrs->size++;
            freed_addrs->data[freed_addrs->size - 1] = addr;
        }
    }
}

void linkedstack_addrs_del(addrs *freed_addrs, void *addr)
{
    for (size_t i = 0; i < freed_addrs->size; i++)
        if (freed_addrs->data[i] == addr)
        {
            void *temp = freed_addrs->data[freed_addrs->size - 1];
            freed_addrs->data[freed_addrs->size - 1] = freed_addrs->data[i];
            freed_addrs->data[i] = temp;
            freed_addrs->size--;
        }
}

void linkedstack_addrs_print(addrs *freed_addrs)
{
    for (size_t i = 0; i < freed_addrs->size; i++)
        printf("%p ", freed_addrs->data[i]);
    printf("\n");
}

int linkedstack_empty(void *stack)
{
    return !(((linked_list_stack_t *)stack)->head);
}

void linkedstack_init(linked_list_stack_t *stack)
{
    stack->head = NULL;
}

int linkedstack_scan(linked_list_stack_t *stack, addrs *freed_addrs)
{
    int rc = 0;

    linkedstack_init(stack);

    int temp;
    while (scanf("%d", &temp) == 1)
        if ((rc = linkedstack_add(stack, temp, freed_addrs)))
            return rc;

    fflush(stdin);

    return EXIT_SUCCESS;
}

int linkedstack_print(linked_list_stack_t *stack, addrs *freed_addrs)
{
    int rc = 0;

    while (stack->head)
    {
        int last;
        void *addr = NULL;

        if ((rc = linkedstack_pop(stack, &last, &addr, freed_addrs)))
            return rc;

        printf("[%p: %d]", addr, last);
    }

    printf("\n");

    return EXIT_SUCCESS;
}

int linkedstack_add(linked_list_stack_t *stack, int elem, addrs *freed_addrs)
{
    node_t *new = malloc(LINKED_LIST_STACK_SIZE_ELEM);
    if (new == NULL)
        return EXIT_ALLOCATING_NODE_ERROR;

    new->data = elem;
    new->next = stack->head;
    stack->head = new;

    linkedstack_addrs_del(freed_addrs, stack->head);

    return EXIT_SUCCESS;
}

void linkedstack_clear_node(node_t *node)
{
    free(node->next);
    free(node);
}

int linkedstack_pop(linked_list_stack_t *stack, int *last, void **addr, addrs *freed_addrs)
{
    if (stack->head == NULL)
        return EXIT_EMPTY_LINKED_LIST_STACK_ERROR;

    node_t *temp;
    if (stack->head->next)
    {
        temp = malloc(LINKED_LIST_STACK_SIZE_ELEM);
        if (temp == NULL)
            return EXIT_ALLOCATING_NODE_ERROR;
        *temp = *stack->head->next;
    }
    else 
        temp = NULL;

    if (last != NULL)
            *last = stack->head->data;
    if (addr != NULL)
            *addr = stack->head;

    linkedstack_addrs_add(freed_addrs, stack->head);

    linkedstack_clear_node(stack->head);

    stack->head = temp;

    return EXIT_SUCCESS;
}

int linkedstack_cmp_node(node_t *n1, node_t *n2)
{
    return n1->data - n2->data;
}

int linkedstack_clear(linked_list_stack_t *stack, addrs *freed_addrs)
{
    int rc = 0;

    while (stack->head)
        if ((rc = linkedstack_pop(stack, NULL, NULL, freed_addrs)))
            return rc;

    return EXIT_SUCCESS;
} 

int linkedstack_move(linked_list_stack_t *dst, linked_list_stack_t *src, addrs *freed_addrs)
{
    int rc = 0;

    linkedstack_init(dst);

    while (src->head)
    {
        int src_last;

        if ((rc = linkedstack_pop(src, &src_last, NULL, freed_addrs)))
            return rc;

        if ((rc = linkedstack_add(dst, src_last, freed_addrs)))
            return rc;
    }

    linkedstack_clear(src, freed_addrs);

    return EXIT_SUCCESS;
}

int linkedstack_sort_descending(linked_list_stack_t *stack, addrs *freed_addrs)
{
    int rc = 0;

    linked_list_stack_t temp;
    linkedstack_init(&temp);

    while (stack->head)
    {
        int stack_last;
        if ((rc = linkedstack_pop(stack, &stack_last, NULL, freed_addrs)))
            return rc;

        while (temp.head && temp.head->data < stack_last)
        {
            int temp_last;

            if ((rc = linkedstack_pop(&temp, &temp_last, NULL, freed_addrs)))
                return rc;

            if ((rc = linkedstack_add(stack, temp_last, freed_addrs)))
                return rc;
        }

        if ((rc = linkedstack_add(&temp, stack_last, freed_addrs)))
            return rc;
    }

    if ((rc = linkedstack_move(stack, &temp, freed_addrs)))
        return rc;

    linkedstack_clear(&temp, freed_addrs);

    return EXIT_SUCCESS;
}

// Сливает два стека в третий, если они отсортированы то и итоговый стек будет отсортирован по возрастанию
int linkedstack_merge(linked_list_stack_t *src1, linked_list_stack_t *src2, linked_list_stack_t *dst, addrs *freed_addrs)
{
    int rc = 0;

    linkedstack_init(dst);

    for (int src1_empty = !src1->head, src2_empty = !src2->head; !src1_empty || !src2_empty; src1_empty = !src1->head, src2_empty = !src2->head)
    {
        // Достаем минимальный элемент из двух стеков, либо оставшиеся элеметы когда один из стеков пустой
        int maxi;
        if (!src1_empty && !src2_empty)
        {
            if (linkedstack_cmp_node(src1->head, src2->head) > 0)
                rc = linkedstack_pop(src1, &maxi, NULL, freed_addrs);
            else
                rc = linkedstack_pop(src2, &maxi, NULL, freed_addrs);
        }
        else if (!src1_empty)
            rc = linkedstack_pop(src1, &maxi, NULL, freed_addrs);
        else
            rc = linkedstack_pop(src2, &maxi, NULL, freed_addrs);

        if (rc)
            return rc;

        linkedstack_add(dst, maxi, freed_addrs);       
    }

    linkedstack_clear(src1, freed_addrs);
    linkedstack_clear(src2, freed_addrs);

    return EXIT_SUCCESS;
}

int linkedstack_to(linked_list_stack_t *src, mystack_t *dst, addrs *freed_addrs)
{
    int rc = 0;

    stack_init(dst);

    while (src->head)
    {
        int src_last;

        if ((rc = linkedstack_pop(src, &src_last, NULL, freed_addrs)))
            return rc;

        if ((rc = stack_add(dst, src_last)))
            return rc;
    }

    linkedstack_clear(src, freed_addrs);

    return EXIT_SUCCESS;
}

int linkedstack_from(linked_list_stack_t *dst, mystack_t *src, addrs *freed_addrs)
{
    int rc = 0;

    linkedstack_init(dst);

    for (int src_empty = !src->head; !src_empty; src_empty = !src->head)
    {
        int src_last;

        if ((rc = stack_pop(src, &src_last)))
            return rc;

        if ((rc = linkedstack_add(dst, src_last, freed_addrs)))
            return rc;
    }

    stack_clear(src);

    return EXIT_SUCCESS;
}

int linkedstack_copy(linked_list_stack_t *src, linked_list_stack_t *copy, addrs *freed_addrs)
{
    int rc = 0;

    linked_list_stack_t src_rev;

    linkedstack_init(&src_rev);
    linkedstack_move(&src_rev, src, freed_addrs);

    linkedstack_init(src);
    linkedstack_init(copy);
    while(src_rev.head)
    {
        int rev_last;

        if ((rc = linkedstack_pop(&src_rev, &rev_last, NULL, freed_addrs)))
            return rc;

        if ((rc = linkedstack_add(src, rev_last, freed_addrs)))
            return rc;

        if ((rc = linkedstack_add(copy, rev_last, freed_addrs)))
            return rc;
    }

    linkedstack_clear(&src_rev, freed_addrs);

    return EXIT_SUCCESS;
}

// Данные добавляются в стек поочередно, таким образом если вывести стек - данные будут выведены наоборот
int linkedstack_from_arr(linked_list_stack_t *dst, int arr[], size_t n, addrs *freed_addrs)
{
    int rc = 0;

    linkedstack_init(dst);

    for (size_t i = 0; i < n; i++)
        if ((rc = linkedstack_add(dst, arr[i], freed_addrs)))
            return rc;

    return EXIT_SUCCESS;
}

unsigned long long linkedstack_sort_merge_time(linked_list_stack_t *stack1, linked_list_stack_t *stack2, addrs *freed_addrs)
{
    unsigned long long sum = 0;

    for (int i = 0; i < TIME_RUNS; i++)
    {
        linked_list_stack_t copy1, copy2, result;
        linkedstack_copy(stack1, &copy1, freed_addrs);
        linkedstack_copy(stack2, &copy2, freed_addrs);

        struct timespec beg, end;

        clock_gettime(CLOCK_MONOTONIC_RAW, &beg);
        linkedstack_sort_descending(&copy1, freed_addrs);
        linkedstack_sort_descending(&copy2, freed_addrs);
        linkedstack_merge(&copy1, &copy2, &result, freed_addrs);
        clock_gettime(CLOCK_MONOTONIC_RAW, &end);

        sum += nanoseconds(&beg, &end);
    }

    return sum / TIME_RUNS;
}

size_t linkedstack_mem(linked_list_stack_t *stack, addrs *freed_addrs)
{
    size_t mem = 0;

    while (stack->head)
    {
        mem += sizeof(*stack->head);
        linkedstack_pop(stack, NULL, NULL, freed_addrs);
    }

    mem += sizeof(linked_list_stack_t);

    return mem;
}
