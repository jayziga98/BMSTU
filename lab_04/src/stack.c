#include "stack.h"

int stack_empty(void *stack)
{
    return !(((mystack_t *)stack)->head);
}

void stack_init(mystack_t *stack)
{
    stack->size = 0;
    stack->head = NULL;
    stack->data = NULL;
}

int stack_scan(mystack_t *stack)
{
    int rc = 0;

    stack_init(stack);

    int temp;
    while (scanf("%d", &temp) == 1)
        if ((rc = stack_add(stack, temp)))
            return rc;

    fflush(stdin);

    return EXIT_SUCCESS;
}

int stack_print(mystack_t *stack)
{
    int rc = 0;

    for (int stack_empty = 0; !stack_empty; stack_empty = !stack->head)
    {
        int last;

        if ((rc = stack_pop(stack, &last)))
            return rc;

        printf("%d ", last);
    }

    printf("\n");

    return EXIT_SUCCESS;
}

int stack_add(mystack_t *stack, int elem)
{
    if (stack->data == NULL)
    {
        stack->data = malloc(STACK_SIZE_ELEM);
        if (stack->data == NULL)
            return EXIT_ALLOCATING_STACK_ERROR;

        stack->size = 1;
        stack->head = &(stack->data[stack->size - 1]);
        *(stack->head) = elem;
    }
    else
    {
        int *temp = realloc(stack->data, STACK_SIZE_ELEM * (stack->size + 1));
        if (temp == NULL)
            return EXIT_STACK_ADD_MEM_ERROR;

        stack->data = temp;
        stack->size++;
        stack->head = &(stack->data[stack->size - 1]);
        *(stack->head) = elem;
    }

    return EXIT_SUCCESS;
}

// last - возвращает последний элемент
// last == NULL - если последний элемент не нужен
int stack_pop(mystack_t *stack, int *last)
{
    if (stack->data == NULL)
        return EXIT_UNINITIALIZED_STACK_ERROR;
    if (!stack->head)
        return EXIT_EMPTY_STACK_ERROR;

    if (last != NULL)
        *last = *stack->head;

    stack->size--;
    int *temp = realloc(stack->data, STACK_SIZE_ELEM * stack->size);
    if (temp == NULL)
        return EXIT_STACK_POP_MEM_ERROR;

    if (stack->size)
    {
        stack->data = temp;
        stack->head = &(stack->data[stack->size - 1]);
    }
    else
    {
        stack_init(stack);
    }

    return EXIT_SUCCESS;
}

void stack_clear(mystack_t *stack)
{
    free(stack->data);
    stack_init(stack);
}

int stack_move(mystack_t *dst, mystack_t *src)
{
    int rc = 0;

    stack_init(dst);

    for (int src_empty = !src->head; !src_empty; src_empty = !src->head)
    {
        int src_last;

        if ((rc = stack_pop(src, &src_last)))
            return rc;

        if ((rc = stack_add(dst, src_last)))
            return rc;
    }

    stack_clear(src);

    return EXIT_SUCCESS;
}

int stack_copy(mystack_t *src, mystack_t *copy)
{
    int rc = 0;

    mystack_t src_rev;

    stack_init(&src_rev);
    stack_move(&src_rev, src);

    stack_init(src);
    stack_init(copy);
    for (int rev_empty = !src_rev.head; !rev_empty; rev_empty = !src_rev.head)
    {
        int rev_last;

        if ((rc = stack_pop(&src_rev, &rev_last)))
            return rc;

        if ((rc = stack_add(src, rev_last)))
            return rc;

        if ((rc = stack_add(copy, rev_last)))
            return rc;
    }

    stack_clear(&src_rev);

    return EXIT_SUCCESS;
}

int stack_sort_descending(mystack_t *stack)
{
    int rc = 0;

    mystack_t temp;
    stack_init(&temp);

    for (int stack_empty = !stack->head; !stack_empty; stack_empty = !stack->head)
    {
        int stack_last;
        if ((rc = stack_pop(stack, &stack_last)))
            return rc;

        for (int temp_empty = !temp.head; !temp_empty && *(temp.head) < stack_last; temp_empty = !temp.head)
        {
            int temp_last;

            if ((rc = stack_pop(&temp, &temp_last)))
                return rc;

            if ((rc = stack_add(stack, temp_last)))
                return rc;
        }
        if ((rc = stack_add(&temp, stack_last)))
            return rc;
    }

    if ((rc = stack_move(stack, &temp)))
        return rc;

    return EXIT_SUCCESS;
}

// Сливает два стека в третий, если они отсортированы то и итоговый стек будет отсортирован по возрастанию
int stack_merge(mystack_t *src1, mystack_t *src2, mystack_t *dst)
{
    int rc = 0;

    stack_init(dst);

    for (int src1_empty = !src1->head, src2_empty = !src2->head; !src1_empty || !src2_empty; src1_empty = !src1->head, src2_empty = !src2->head)
    {
        // Достаем минимальный элемент из двух стеков, либо оставшиеся элеметы когда один из стеков пустой
        int maxi;
        if (!src1_empty && !src2_empty)
        {
            if (*src1->head > *src2->head)
                rc = stack_pop(src1, &maxi);
            else
                rc = stack_pop(src2, &maxi);
        }
        else if (!src1_empty)
            rc = stack_pop(src1, &maxi);
        else
            rc = stack_pop(src2, &maxi);

        if (rc)
            return rc;

        stack_add(dst, maxi);       
    }

    stack_clear(src1);
    stack_clear(src2);

    return EXIT_SUCCESS;
}

// Данные добавляются в стек поочередно, таким образом если вывести стек - данные будут выведены наоборот
int stack_from_arr(mystack_t *dst, int arr[], size_t n)
{
    int rc = 0;

    stack_init(dst);

    for (size_t i = 0; i < n; i++)
        if ((rc = stack_add(dst, arr[i])))
            return rc;

    return EXIT_SUCCESS;
}

unsigned long long stack_sort_merge_time(mystack_t *stack1, mystack_t *stack2)
{
    unsigned long long sum = 0;

    for (int i = 0; i < TIME_RUNS; i++)
    {
        mystack_t copy1, copy2, result;
        stack_copy(stack1, &copy1);
        stack_copy(stack2, &copy2);

        struct timespec beg, end;

        clock_gettime(CLOCK_MONOTONIC_RAW, &beg);
        stack_sort_descending(&copy1);
        stack_sort_descending(&copy2);
        stack_merge(&copy1, &copy2, &result);
        clock_gettime(CLOCK_MONOTONIC_RAW, &end);

        sum += nanoseconds(&beg, &end);
    }

    return sum / TIME_RUNS;
}

size_t stack_mem(mystack_t *stack)
{
    size_t mem = 0;

    for (int stack_empty = 0; !stack_empty; stack_empty = !stack->head)
    {
        mem += sizeof(stack->head);
        stack_pop(stack, NULL);
    }

    mem += sizeof(mystack_t);

    return mem;
}
