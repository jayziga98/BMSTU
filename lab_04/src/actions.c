#include "actions.h"

void info_print()
{
    printf("+_____________________________________________________________________+\n");
    printf("| Программа позволяет работать со структурой данных под названием стек|\n");
    printf("| Есть возможность:                                                   |\n");
    printf("|     1. Выбрать реализацию с помощью односвязного списка             |\n");
    printf("|     2. Выбрать стандартную реализацию [По умолчанию]                |\n");
    printf("| Ввести целые числа в 2 стека.                                       |\n");
    printf("| Используя третий стек отсортировать все введенные данные.           |\n");
    printf("+_____________________________________________________________________+\n");
}

int actions_print(char type[STACK_TYPE_LEN])
{
    int com = 0;

    printf("\n");

    // 0
    printf("|> %*d - %-s\n", COMMAND_NUMBER_LEN, com, "Завершить."), com++;
    // 1
    char type_com[STACK_TYPE_LEN * 3];
    strcpy(type_com, "Поменять тип стека [сейчас: ");
    strcat(type_com, type);
    strcat(type_com, "]");
    printf("|> %*d - %-s\n", COMMAND_NUMBER_LEN, com, type_com), com++;
    // 2
    printf("|> %*d - %-s\n", COMMAND_NUMBER_LEN, com, "Сравнить эффективность для пункта 15."), com++;
    // 3
    printf("|> %*d - %-s\n", COMMAND_NUMBER_LEN, com, "Сравнить объем памяти."), com++;
    // 4
    printf("|> %*d - %-s\n", COMMAND_NUMBER_LEN, com, "Вывести свободные адреса."), com++;

    printf("\n");

    printf("|Первый стек\n|\n");
    // 5
    printf("|> %*d - %-s\n", COMMAND_NUMBER_LEN, com, "Ввести."), com++;

    printf("|\n");

    // 6
    printf("|> %*d - %-s\n", COMMAND_NUMBER_LEN, com, "Напечатать."), com++;
    // 7
    printf("|> %*d - %-s\n", COMMAND_NUMBER_LEN, com, "Напечатать КОПИЮ."), com++;

    printf("|\n");

    // 8
    printf("|> %*d - %-s\n", COMMAND_NUMBER_LEN, com, "Добавить элемент."), com++;

    printf("|\n");

    // 9
    printf("|> %*d - %-s\n", COMMAND_NUMBER_LEN, com, "Удалить элемент."), com++;

    printf("\n");

    printf("|Второй стек\n|\n");
    // 10
    printf("|> %*d - %s\n", COMMAND_NUMBER_LEN, com, "Ввести."), com++;

    printf("|\n");

    // 11
    printf("|> %*d - %s\n", COMMAND_NUMBER_LEN, com, "Напечатать."), com++;
    // 12
    printf("|> %*d - %-s\n", COMMAND_NUMBER_LEN, com, "Напечатать КОПИЮ."), com++;

    printf("|\n");

    // 13
    printf("|> %*d - %s\n", COMMAND_NUMBER_LEN, com, "Добавить элемент."), com++;

    printf("|\n");

    // 14
    printf("|> %*d - %s\n", COMMAND_NUMBER_LEN, com, "Удалить элемент."), com++;

    printf("\n");

    printf("|Третий стек\n|\n");
    // 15
    printf("|> %*d - %s\n", COMMAND_NUMBER_LEN, com, "Слить первый и второй стеки в третий."), com++;

    printf("|\n");

    // 16
    printf("|> %*d - %s\n", COMMAND_NUMBER_LEN, com, "Напечатать."), com++;
    // 17
    printf("|> %*d - %-s\n", COMMAND_NUMBER_LEN, com, "Напечатать КОПИЮ."), com++;

    printf("|\n");

    // 18
    printf("|> %*d - %s\n", COMMAND_NUMBER_LEN, com, "Добавить элемент."), com++;

    printf("|\n");

    // 19
    printf("|> %*d - %s\n", COMMAND_NUMBER_LEN, com, "Удалить элемент."), com++;

    printf("\n");

    return com - 1;
}

int actions_handler(int com, mystack_t *stack1, mystack_t *stack2, mystack_t *stack3, linked_list_stack_t *llstack1, linked_list_stack_t *llstack2, linked_list_stack_t *llstack3, char type[STACK_TYPE_LEN], addrs *freed_addrs)
{
    switch (com)
    {
    case 0:
        break;
    case 1:
        exec_change_stack_type(stack1, stack2, stack3, llstack1, llstack2, llstack3, type, freed_addrs);
        break;
    case 2:
        exec_time_cmp(freed_addrs);
        break;
    case 3:
        exec_mem_cmp(freed_addrs);
        break;
    case 4:
        exec_print_freed(freed_addrs);
        break;
    case 5:
        return exec_scan(stack1, llstack1, type, freed_addrs);
    case 6:
        return exec_print(stack1, llstack1, type, freed_addrs, 0);
    case 7:
        return exec_print(stack1, llstack1, type, freed_addrs, 1);
    case 8:
        return exec_add(stack1, llstack1, type, freed_addrs);
    case 9:
        return exec_pop(stack1, llstack1, type, freed_addrs);
    case 10:
        return exec_scan(stack2, llstack2, type, freed_addrs);
    case 11:
        return exec_print(stack2, llstack2, type, freed_addrs, 0);
    case 12:
        return exec_print(stack2, llstack2, type, freed_addrs, 1);
    case 13:
        return exec_add(stack2, llstack2, type, freed_addrs);
    case 14:
        return exec_pop(stack2, llstack3, type, freed_addrs);
    case 15:
        return exec_merge_sort(stack1, stack2, stack3, llstack1, llstack2, llstack3, type, freed_addrs);
    case 16:
        return exec_print(stack3, llstack3, type, freed_addrs, 0);
    case 17:
        return exec_print(stack3, llstack3, type, freed_addrs, 1);
    case 18:
        return exec_add(stack3, llstack3, type, freed_addrs);
    case 19:
        return exec_pop(stack3, llstack3, type, freed_addrs);
    default:
        break;
    }

    return EXIT_SUCCESS;
}

int exec_change_stack_type(mystack_t *stack1, mystack_t *stack2, mystack_t *stack3, linked_list_stack_t *llstack1, linked_list_stack_t *llstack2, linked_list_stack_t *llstack3, char type[STACK_TYPE_LEN], addrs *freed_addrs)
{
    int rc = 0;

    int (*convert)(linked_list_stack_t *, mystack_t *, addrs *) = NULL;
    int (*empty)(void *) = NULL;
    void *s1 = NULL;
    void *s2 = NULL;
    void *s3 = NULL;

    if (!strcmp(type, STACK_TYPE_CLASSIC))
    {
        strcpy(type, STACK_TYPE_LINKED_LIST);
        convert = linkedstack_from;
        empty = linkedstack_empty;
        s1 = llstack1;
        s2 = llstack2;
        s3 = llstack3;
    }
    else
    {
        strcpy(type, STACK_TYPE_CLASSIC);
        convert = linkedstack_to;
        empty = stack_empty;
        s1 = stack1;
        s2 = stack2;
        s3 = stack3;
    }

    fflush(stdin);
    char ask;
    printf("\t ? Желаете перенести данные [Y\\n]: ");
    if (scanf("%c", &ask) == 1 && ask != 'n')
    {
        if ((rc = convert(llstack1, stack1, freed_addrs)))
            return rc;

        if (!empty(s1))
            printf("\n\t < Данные из первого стека успешно перенесены!\n");
        else
            printf("\n\t < Первый стек не инициализирован!\n");

        if ((rc = convert(llstack2, stack2, freed_addrs)))
            return rc;

        if (!empty(s2))
            printf("\n\t < Данные из второго стека успешно перенесены!\n");
        else
            printf("\n\t < Второй стек не инициализирован!\n");

        if ((rc = convert(llstack3, stack3, freed_addrs)))
            return rc;

        if (!empty(s3))
            printf("\n\t < Данные из третьего стека успешно перенесены!\n");
        else
            printf("\n\t < Третий стек не инициализирован!\n");
    }

    return EXIT_SUCCESS;
}

int exec_scan(mystack_t *stack, linked_list_stack_t *llstack, char type[STACK_TYPE_LEN], addrs *freed_addrs)
{
    int rc = 0;

    printf("\t ! Ввод элементов производится до неправильного символа - любой непробельный символ и не цифра\n");
    printf("\nВведите элементы стека: ");

    if (!strcmp(type, STACK_TYPE_CLASSIC) && (rc = stack_scan(stack)))
        return rc;   
        
    if (!strcmp(type, STACK_TYPE_LINKED_LIST) && (rc = linkedstack_scan(llstack, freed_addrs)))
        return rc;     

    printf("\n\t < Стек успешно введен!\n");

    return EXIT_SUCCESS;
}

int exec_print(mystack_t *stack, linked_list_stack_t *llstack, char type[STACK_TYPE_LEN], addrs *freed_addrs, int copy)
{
    int rc = 0;

    if (!strcmp(type, STACK_TYPE_CLASSIC))
    {
        mystack_t stcopy;

        if (copy)
        {
            if ((rc = stack_copy(stack, &stcopy)))
                return rc;
            if ((rc = stack_print(&stcopy)))
                return rc;
        }
        else if ((rc = stack_print(stack)))
            return rc;
    }

    if (!strcmp(type, STACK_TYPE_LINKED_LIST))
    {
        linked_list_stack_t llcopy;

        if (copy)
        {
            if ((rc = linkedstack_copy(llstack, &llcopy, freed_addrs)))
                return rc;
            if ((rc = linkedstack_print(&llcopy, freed_addrs)))
                return rc;
        }
        else if ((rc = linkedstack_print(llstack, freed_addrs)))
            return rc;
    }

    return EXIT_SUCCESS;
}

int exec_add(mystack_t *stack, linked_list_stack_t *llstack, char type[STACK_TYPE_LEN], addrs *freed_addrs)
{
    int rc = 0;

    int new;
    printf("Введите число, которое хотите добавить в стек: ");
    while (scanf("%d", &new) != 1)
    {
        fflush(stdin);

        printf("\n\t ! Кажется, вы ошиблись, попробуйте еще раз.\n");
        printf("\t ! Число должно содержать только цифры, после того как ввели нажмите ENTER.\n\n");

        printf("Ваше число: ");
    }

    if (!strcmp(type, STACK_TYPE_CLASSIC) && (rc = stack_add(stack, new)))
        return rc;   
        
    if (!strcmp(type, STACK_TYPE_LINKED_LIST) && (rc = linkedstack_add(llstack, new, freed_addrs)))
        return rc; 

    printf("\n\t < Число успешно добавлен в стек!\n");

    return EXIT_SUCCESS;
}

int exec_pop(mystack_t *stack, linked_list_stack_t *llstack, char type[STACK_TYPE_LEN], addrs *freed_addrs)
{
    int rc = 0;

    int popped;

    if (!strcmp(type, STACK_TYPE_CLASSIC) && (rc = stack_pop(stack, &popped)))
        return rc;   
        
    if (!strcmp(type, STACK_TYPE_LINKED_LIST) && (rc = linkedstack_pop(llstack, &popped, NULL, freed_addrs)))
        return rc; 

    char ask;
    fflush(stdin);
    printf("\n\t ? Вывести удаленный элемент [Y\\n]: ");
    if (scanf("%c", &ask) == 1 && ask != 'n')
        printf("\n\t < Удаленное число: %d\n", popped);

    printf("\n\t < Элемент успешно удален из стека!\n");

    return EXIT_SUCCESS;
}

int exec_merge_sort(mystack_t *stack1, mystack_t *stack2, mystack_t *stack3, linked_list_stack_t *llstack1, linked_list_stack_t *llstack2, linked_list_stack_t *llstack3, char type[STACK_TYPE_LEN], addrs *freed_addrs)
{
    int rc = 0;

    if (!strcmp(type, STACK_TYPE_CLASSIC))
    {
        if ((rc = stack_sort_descending(stack1)))
            return rc;

        if ((rc = stack_sort_descending(stack2)))
            return rc;

        if ((rc = stack_merge(stack1, stack2, stack3)))
            return rc;
    }
    
    if (!strcmp(type, STACK_TYPE_LINKED_LIST))
    {
        if ((rc = linkedstack_sort_descending(llstack1, freed_addrs)))
            return rc;

        if ((rc = linkedstack_sort_descending(llstack2, freed_addrs)))
            return rc;

        if ((rc = linkedstack_merge(llstack1, llstack2, llstack3, freed_addrs)))
            return rc;
    }

    printf("\t < Данные успешно слиты и отсортированы в третий стек!\n");

    return EXIT_SUCCESS;
}

void time_cmp_by(size_t n, void (fill_arr1)(int *, size_t n), void (fill_arr2)(int *, size_t n), addrs *freed_addrs)
{
    mystack_t stack1, stack2;
    linked_list_stack_t llstack1, llstack2;

    unsigned long long time_llst, time_st;
    int a[DATA_MAX_ARRAY_SIZE], b[DATA_MAX_ARRAY_SIZE];

    fill_arr1(a, n);
    fill_arr2(b, n);

    stack_from_arr(&stack1, a, n);
    linkedstack_from_arr(&llstack1, a, n, freed_addrs);
    stack_from_arr(&stack2, b, n);
    linkedstack_from_arr(&llstack2, b, n, freed_addrs);

    time_llst = linkedstack_sort_merge_time(&llstack1, &llstack2, freed_addrs);
    time_st = stack_sort_merge_time(&stack1, &stack2);

    printf("%*llu|%*llu|", TIME_TABLE_NUM_LEN, time_st, TIME_TABLE_NUM_LEN, time_llst);

    linkedstack_clear(&llstack1, freed_addrs);
    linkedstack_clear(&llstack2, freed_addrs);
    stack_clear(&stack1);
    stack_clear(&stack2);
}

void exec_time_cmp(addrs *freed_addrs)
{
    printf("Asc - возрастающая последовательность\n");
    printf("Desc - убывающая последовательность\n");
    printf("Rand - случайная последовательность\n");

    printf("\nStd - стандартная реализация стека\n");
    printf("\nList - реализация стека с помощью связного списка\n");

    printf("\nns - наносекунды\n");

    int table_width = 6 * (TIME_TABLE_NUM_LEN * 2 + 1) + 4 + 8;

    printf("\n");
    for (int i = 0; i < table_width; i++)
        printf("_");
    printf("\n");

    printf("|%*s|%*s|%*s|%*s|", 4, "-", TIME_TABLE_NUM_LEN * 2 + 1, "Asc+Asc", TIME_TABLE_NUM_LEN * 2 + 1, "Asc+Desc", TIME_TABLE_NUM_LEN * 2 + 1, "Asc+Rand");
    printf("%*s|%*s|%*s|", TIME_TABLE_NUM_LEN * 2 + 1, "Desc+Desc", TIME_TABLE_NUM_LEN * 2 + 1, "Desc+Rand", TIME_TABLE_NUM_LEN * 2 + 1, "Rand+Rand");

    printf("\n");
    for (int i = 0; i < table_width; i++)
        printf("_");
    printf("\n");

    printf("|%*s|", 4, "Size");
    for (int i = 0; i < 6; i++)
        printf("%*s|%*s|", TIME_TABLE_NUM_LEN, "Std, ns", TIME_TABLE_NUM_LEN, "List, ns");

    printf("\n");
    for (int i = 0; i < table_width; i++)
        printf("_");
    printf("\n");

    for (size_t n = 1; n <= DATA_MAX_ARRAY_SIZE; n += (n == 1 ? 9 : 10))
    {
        printf("|%4zu|", n);

        // Возрастающая последовательность + Возрастающая последовательность 
        time_cmp_by(n, fill_arr_ascending, fill_arr_ascending, freed_addrs);

        // Возрастающая последовательность + Убывающая последовательность 
        time_cmp_by(n, fill_arr_ascending, fill_arr_descending, freed_addrs);

        // Возрастающая последовательность + Случайная последовательность 
        time_cmp_by(n, fill_arr_ascending, fill_arr_rand, freed_addrs);

        // Убывающая последовательность + Убывающая последовательность 
        time_cmp_by(n, fill_arr_descending, fill_arr_descending, freed_addrs);

        // Убывающая последовательность + Случайная последовательность 
        time_cmp_by(n, fill_arr_descending, fill_arr_rand, freed_addrs);

        // Случайная последовательность + Случайная последовательность 
        time_cmp_by(n, fill_arr_rand, fill_arr_rand, freed_addrs);

        printf("\n");
        for (int i = 0; i < table_width; i++)
            printf("_");
        printf("\n");
    }
}

void exec_mem_cmp(addrs *freed_addrs)
{
    printf("\nStd - стандартная реализация стека\n");
    printf("\nList - реализация стека с помощью связного списка\n");

    printf("\nb - байты\n");

    int table_width = (TIME_TABLE_NUM_LEN * 2 + 1) + 4 + 3;

    printf("\n");
    for (int i = 0; i < table_width; i++)
        printf("_");
    printf("\n");

    printf("|%*s|", 4, "Size");
    printf("%*s|%*s|", TIME_TABLE_NUM_LEN, "Std, b", TIME_TABLE_NUM_LEN, "List, b");

    printf("\n");
    for (int i = 0; i < table_width; i++)
        printf("_");
    printf("\n");

    int a[DATA_MAX_ARRAY_SIZE];
    linked_list_stack_t llstack;
    mystack_t stack;

    for (size_t n = 1; n <= DATA_MAX_ARRAY_SIZE; n += (n == 1 ? 9 : 10))
    {
        size_t llstmem, stmem; 
        printf("|%4zu|", n);

        fill_arr_ascending(a, n);
        linkedstack_from_arr(&llstack, a, n, freed_addrs);
        stack_from_arr(&stack, a, n);

        llstmem = linkedstack_mem(&llstack, freed_addrs);
        stmem = stack_mem(&stack);

        printf("%*zu|%*zu|", TIME_TABLE_NUM_LEN, stmem, TIME_TABLE_NUM_LEN, llstmem);

        printf("\n");
        for (int i = 0; i < table_width; i++)
            printf("_");
        printf("\n");
    }

    linkedstack_clear(&llstack, freed_addrs);
    stack_clear(&stack);
}

void exec_print_freed(addrs *freed_addrs)
{
    if (!freed_addrs->size)
        printf("\t < Массив свободных адресов пуст\n");
    else
    {
        printf("\t < Массив свободных адресов: ");
        linkedstack_addrs_print(freed_addrs);
    }
}
