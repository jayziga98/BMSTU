#include <stdio.h>
#include <stdlib.h>

#include "actions.h"
#include "stack.h"
#include "linked_list_stack.h"

int error_handler(int rc);

int main()
{
    info_print();

    int max_com = 0;

    char type[STACK_TYPE_LEN];
    strcpy(type, STACK_TYPE_CLASSIC);

    mystack_t stack1, stack2, stack3;
    stack_init(&stack1);
    stack_init(&stack2);
    stack_init(&stack3);

    linked_list_stack_t llstack1, llstack2, llstack3;
    linkedstack_init(&llstack1);
    linkedstack_init(&llstack2);
    linkedstack_init(&llstack3);

    addrs freed_addrs;
    freed_addrs.size = 0;

    for (int com = -1, com_cnt = 0; com != 0; com_cnt++, com_cnt %= 3)
    {
        if (!com_cnt)
            max_com = actions_print(type);

        int rc = 0;

        printf("\n > Выполнить команду №: ");
        fflush(stdin);
        if (scanf("%d", &com) == 1)
        {
            printf("\n");

            rc = actions_handler(com, &stack1, &stack2, &stack3, &llstack1, &llstack2, &llstack3, type, &freed_addrs);

            if (rc)
                return error_handler(rc);
        }
        else
            printf("\n\t ? Введите цифру от 0 до %d\n", max_com);
    }

    stack_clear(&stack1);
    stack_clear(&stack2);
    stack_clear(&stack3);

    linkedstack_clear(&llstack1, &freed_addrs);
    linkedstack_clear(&llstack2, &freed_addrs);
    linkedstack_clear(&llstack3, &freed_addrs);

    return EXIT_SUCCESS;
}

int error_handler(int rc)
{
    switch (rc)
    {
        case EXIT_ALLOCATING_NODE_ERROR:
            printf("Ошибка: Выделение памяти под новый узел не удалось!");
            break;
        case EXIT_EMPTY_LINKED_LIST_STACK_ERROR:
            printf("Ошибка: Вы пытаетесь произвести операцию над пустым стеком в виде односвязного списка!");
            break;
        case EXIT_ALLOCATING_STACK_ERROR:
            printf("Ошибка: Выделение памяти под стек не удалось!");
            break;
        case EXIT_STACK_ADD_MEM_ERROR:
            printf("Ошибка: Добавление памяти для нового элемента стека не удалось!");
            break;
        case EXIT_EMPTY_STACK_ERROR:
            printf("Ошибка: Вы пытаетесь произвести операцию над пустым стеком!");
            break;
        case EXIT_UNINITIALIZED_STACK_ERROR:
            printf("Ошибка: Вы пытаетесь произвести операцию над неинициализированным стеком!");
            break;
        case EXIT_STACK_POP_MEM_ERROR:
            printf("Ошибка: Очищение памяти при удалении элемента из стека не удалось!");
            break;
        default:
            printf("Ошибка: Неизвестная ошибка!");
    }

    return rc;
}