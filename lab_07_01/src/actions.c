#include "actions.h"

void info_print()
{
    printf("+____________________________________________________________________________________________+\n");
    printf("| Программа позволяет выполнять операции над введеной строкой с помощью:                     |\n");
    printf("|           Scapegoat tree - сбалансированного бинарного дерева поиска                       |\n"); 
    printf("|           Двочиного дерева поиска                                                          |\n"); 
    printf("|           Хэш-таблицы                                                                      |\n"); 
    printf("| Возможности:                                                                               |\n"); 
    printf("|           Построить структуры из букв вводимой строки.                                     |\n"); 
    printf("|           Вывести структуры на экран.                                                      |\n"); 
    printf("|           Удалить из дерева буквы, которые встречаются более одного раза.                  |\n"); 
    printf("|           Сравнить время работы данных структур                                            |\n"); 
    printf("|           Сравнить объем занимаемой памяти данных структур                                 |\n"); 
    printf("+____________________________________________________________________________________________+\n");
}

int actions_print()
{
    int com = 0;

    printf("\n");

    // 0
    printf("|> %*d - %-s\n", COMMAND_NUMBER_LEN, com, "Завершить."), com++;

    printf("|\n");

    // 1
    printf("|> %*d - %-s\n", COMMAND_NUMBER_LEN, com, "Построить структуры из чисел."), com++;
    // 2
    printf("|> %*d - %-s\n", COMMAND_NUMBER_LEN, com, "Добавить число."), com++;
    // 3
    printf("|> %*d - %-s\n", COMMAND_NUMBER_LEN, com, "Удалить число."), com++;

    printf("|\n");
    
    // 4
    printf("|> %*d - %-s\n", COMMAND_NUMBER_LEN, com, "Удалить числа, встречающиеся более одного раза"), com++;

    printf("|\n");

    // 5
    printf("|> %*d - %-s\n", COMMAND_NUMBER_LEN, com, "Напечатать структуры."), com++;

    printf("|\n");

    // 6
    printf("|> %*d - %-s\n", COMMAND_NUMBER_LEN, com, "Сравнить эффективность."), com++;
    // 7
    printf("|> %*d - %-s\n", COMMAND_NUMBER_LEN, com, "Сравнить объем занимаемой памяти."), com++;

    printf("\n");

    return com - 1;
}

int actions_handler(int com, hash_table_open_t *table, scapegoat_tree_t *stree, binary_tree_t *btree)
{
    switch (com)
    {
    case 0:
        break;
    case 1:
        return exec_scan_from_string(table, stree, btree);
    case 2:
        return exec_add(table, stree, btree);
    case 3:
        exec_del(table, stree, btree);
        break;
    case 4:
        exec_del_ununique(table, stree, btree);
        break;
    case 5:
        exec_print(table, stree, btree);
        break;
    case 6:
        exec_time_cmp_del_ununique();
        exec_time_cmp_add();
        exec_time_cmp_del();
        exec_time_cmp_find();
        break;
    case 7:
        exec_mem_cmp();
        break;
    default:
        break;
    }

    return EXIT_SUCCESS;
}

int exec_scan_from_string(hash_table_open_t *table, scapegoat_tree_t *stree, binary_tree_t *btree)
{
    int rc = 0;

    arr_ints_t s;
    fflush(stdin);
    ints_scan(&s, ARR_SIZE, stdin);
    if ((rc = scapegoat_scan_from(stree, &s)) || (rc = btree_scan_from(btree, &s)))
        return rc;

    hashtableopen_from(table, &s);
    printf("\t < Структуры успешно построены\n");

    return EXIT_SUCCESS;
}

int exec_add(hash_table_open_t *table, scapegoat_tree_t *stree, binary_tree_t *btree)
{
    int rc = 0;

    int c;

    fflush(stdin);
    if (scanf("%d", &c) != 1)
    {
        printf("\n\t ! Элемент должен быть числом.\n");
        return 0;
    }
    fflush(stdin);

    if ((rc = btree_add(&(btree->root), c, NULL)))
        return rc;
    if ((rc = scapegoat_add(&(stree->root), c, NULL, 1)))
        return rc;

    hashtableopen_add(table, c, 1);

    printf("\t < Число успешно добавлено.\n");

    return EXIT_SUCCESS;
}

void exec_del(hash_table_open_t *table, scapegoat_tree_t *stree, binary_tree_t *btree)
{
    int c;

    fflush(stdin);
    if (scanf("%d", &c) != 1)
    {
        printf("\n\t ! Элемент должен быть числом.\n");
        return;
    }
    fflush(stdin);

    btree_del(&(btree->root), c);
    scapegoat_del(&(stree->root), c);
    hashtableopen_del(table, c);

    printf("\t < Число успешно удалено.\n");
}

void exec_del_ununique(hash_table_open_t *table, scapegoat_tree_t *stree, binary_tree_t *btree)
{
    btree_del_ununique(&(btree->root));
    scapegoat_del_ununique(&(stree->root));
    hashtableopen_del_ununique(table);

    printf("\t < Не уникальные числа успешно удалены.\n");
}

void exec_print(hash_table_open_t *table, scapegoat_tree_t *stree, binary_tree_t *btree)
{
    printf("+~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~+\n");
    printf("|               Дерево                |\n");
    printf("+~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~+\n");

    btree_print_tree(btree->root);
    printf("\n");

    printf("+~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~+\n");
    printf("|       Сбалансированное дерево       |\n");
    printf("+~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~+\n");

    scapegoat_print_tree(stree->root);
    printf("\n");

    printf("+~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~+\n");
    printf("|             Хэш-таблица             |\n");
    printf("+~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~+\n");

    printf("\n");
    hashtableopen_print(table);
}

void exec_time_cmp_del_ununique()
{
    printf("Время замеряется сто раз и высчитывается среднее значение \n\n");
    printf("Размер\tДерево, нс\tСбалансированное дерево, нс\tХэш-таблица, нс\n");
    FILE *f = fopen("dataset.txt", "r");
    arr_ints_t s;
    size_t n = 6;
    size_t sizes[20] = { 1, 10, 50, 100, 1000, 3000 };
    for (size_t i = 0; i < n; i++)
    {
        ints_scan(&s, sizes[i], f);
        printf("%zu\t\t%llu\t\t%llu\t\t\t%llu\n", sizes[i], btree_del_ununique_time(&s), scapegoat_del_ununique_time(&s), hashtableopen_del_ununique_time(&s));
    }

    fclose(f);

    printf("\n");
}

void exec_time_cmp_del()
{
    printf("Вычисляется среднее время удаления случайного элемента из дерева \n");
    printf("Замеры выполняются %d раз и высчитывается среднее значение \n\n", TIME_RUNS);
    printf("\t\tУдаление\n\n");
    printf("Размер\tДерево, нс\tСбалансированное дерево, нс\tХэш-таблица, нс\n");
    FILE *f = fopen("dataset.txt", "r");
    arr_ints_t s;
    size_t n = 6;
    size_t sizes[20] = { 1, 10, 50, 100, 1000, 3000 };
    for (size_t i = 0; i < n; i++)
    {
        ints_scan(&s, sizes[i], f);

        printf("%zu\t\t%llu\t\t%llu\t\t\t%llu\n", sizes[i], btree_del_time(&s), scapegoat_del_time(&s), hashtableopen_del_time(&s));
    }

    fclose(f);

    printf("\n");
}

void exec_time_cmp_add()
{
    printf("Вычисляется среднее время добавления случайного элемента в дерево \n");
    printf("Замеры выполняются %d раз и высчитывается среднее значение \n\n", TIME_RUNS);
    printf("\t\tДобавление\n\n");
    printf("Размер\tДерево, нс\tСбалансированное дерево, нс\tХэш-таблица, нс\n");
    FILE *f = fopen("dataset.txt", "r");
    arr_ints_t s;
    size_t n = 6;
    size_t sizes[20] = { 1, 10, 50, 100, 1000, 3000 };
    for (size_t i = 0; i < n; i++)
    {
        ints_scan(&s, sizes[i], f);

        printf("%zu\t\t%llu\t\t%llu\t\t\t%llu\n", sizes[i], btree_add_time(&s), scapegoat_add_time(&s), hashtableopen_add_time(&s));
    }

    fclose(f);

    printf("\n");
}

void exec_time_cmp_find()
{
    printf("Вычисляется среднее время добавления случайного элемента в дерево \n");
    printf("Замеры выполняются %d раз и высчитывается среднее значение \n\n", TIME_RUNS);
    printf("\t\tПоиск\n\n");
    printf("Размер\tДерево, нс\tСбалансированное дерево, нс\tХэш-таблица, нс\n");
    FILE *f = fopen("dataset.txt", "r");
    arr_ints_t s;
    size_t n = 6;
    size_t sizes[20] = { 1, 10, 50, 100, 1000, 3000 };
    for (size_t i = 0; i < n; i++)
    {
        ints_scan(&s, sizes[i], f);

        printf("%zu\t\t%llu\t\t%llu\t\t\t%llu\n", sizes[i], btree_find_time(&s), scapegoat_find_time(&s), hashtableopen_find_time(&s));
    }

    fclose(f);

    printf("\n");
}

void exec_mem_cmp()
{
    printf("Строка\n");
    printf("Структура - %zu | 1 Элемент - %zu", sizeof(arr_ints_t), sizeof(char) * ARR_SIZE);

    printf("\n");

    printf("Дерево\n");
    printf("Структура - %zu | 1 Элемент - %zu", btree_struct_mem(), btree_elem_mem());

    printf("\n");

    printf("Сбалансированное Дерево\n");
    printf("Структура - %zu | 1 Элемент - %zu", scapegoat_struct_mem(), scapegoat_elem_mem());

    printf("\n");

    printf("Хэш таблица\n");
    printf("Структура - %zu | 1 Элемент - %zu", hashtableopen_struct_mem(), hashtableopen_elem_mem());

    printf("\n");
}
