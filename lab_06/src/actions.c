#include "actions.h"

void info_print()
{
    printf("+____________________________________________________________________________________________+\n");
    printf("| Программа позволяет работать со структурой данных Бинарное дерево поиска                   |\n");
    printf("|           Реализована модификация Scapegoat tree - сбалансированное бинарное дерево поиска |\n"); 
    printf("| Возможности:                                                                               |\n"); 
    printf("|           Построить двоичное дерево поиска из букв вводимой строки.                        |\n"); 
    printf("|           Вывести его на экран в виде дерева.                                              |\n"); 
    printf("|           Выделить цветом все буквы, встречающиеся более одного раза.                      |\n"); 
    printf("|           Удалить из дерева эти буквы.                                                     |\n"); 
    printf("|           Вывести оставшиеся элементы дерева при постфиксном его обходе.                   |\n"); 
    printf("|           Сравнить время удаления повторяющихся букв из дерева и из строки.                |\n"); 
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
    printf("|> %*d - %-s\n", COMMAND_NUMBER_LEN, com, "Построить дерево из букв вводимой строки."), com++;
    // 2
    printf("|> %*d - %-s\n", COMMAND_NUMBER_LEN, com, "Добавить букву в дерево."), com++;
    // 3
    printf("|> %*d - %-s\n", COMMAND_NUMBER_LEN, com, "Удалить букву из дерева."), com++;

    printf("|\n");
    
    // 4
    printf("|> %*d - %-s\n", COMMAND_NUMBER_LEN, com, "Удалить буквы, встречающиеся более одного раза, и вывести элементы в постфиксном обходе."), com++;

    printf("|\n");

    // 5
    printf("|> %*d - %-s\n", COMMAND_NUMBER_LEN, com, "Напечатать дерево в виде дерева."), com++;

    printf("|\n");

    // 6
    printf("|> %*d - %-s\n", COMMAND_NUMBER_LEN, com, "Сравнить эффективность. (Все пункты)"), com++;
    // 7
    printf("|> %*d - %-s\n", COMMAND_NUMBER_LEN, com, "Время удаления не уникальных букв из дерева и из строки"), com++;
    // 8
    printf("|> %*d - %-s\n", COMMAND_NUMBER_LEN, com, "Время добавления случайного элемента в дерево"), com++;
    // 9
    printf("|> %*d - %-s\n", COMMAND_NUMBER_LEN, com, "Время удаления случайного элемента из дерева"), com++;
    
    printf("|\n");
    
    // 10
    printf("|> %*d - %-s\n", COMMAND_NUMBER_LEN, com, "Сравнить объем занятой памяти."), com++;

    printf("|\n");
    
    // 11
    printf("|> %*d - %-s\n", COMMAND_NUMBER_LEN, com, "Напечатать обходы дерева."), com++;

    printf("\n");

    return com - 1;
}

int actions_handler(int com, binary_tree_t *tree)
{
    switch (com)
    {
    case 0:
        break;
    case 1:
        exec_scapegoat_scan_from(tree);
        break;
    case 2:
        exec_add(tree);
        break;
    case 3:
        exec_del(tree);
        break;
    case 4:
        exec_print_unique_postfix(tree);
        break;
    case 5:
        scapegoat_print_tree(tree->root);
        break;
    case 6:
        exec_time_cmp_del_ununique();
        exec_time_cmp_add();
        exec_time_cmp_del();
        exec_time_cmp_find();
        break;
    case 7:
        exec_time_cmp_del_ununique();
        break;
    case 8:
        exec_time_cmp_add();
        break;
    case 9:
        exec_time_cmp_del();
        break;
    case 10:
        exec_mem_cmp();
        break;
    case 11:
        printf("Префиксный обход: ");
        scapegoat_print_prefix(tree->root);
        printf("\n");
        printf("Инфиксный обход: ");
        scapegoat_print_infix(tree->root);
        printf("\n");
        printf("Постфиксный обход: ");
        scapegoat_print_postfix(tree->root);
        printf("\n");
    default:
        break;
    }

    return EXIT_SUCCESS;
}

int exec_scapegoat_scan_from(binary_tree_t *tree)
{
    int rc = 0;

    my_string_t s;
    fflush(stdin);
    string_scan(s, STR_LEN, stdin);
    for (size_t i = 0; s[i] != '\0'; i++)
        if (isalpha(s[i]))
            if ((rc = scapegoat_add(&(tree->root), s[i], NULL, 1)))
                return rc;

    scapegoat_balance(&(tree->root));
    printf("\t < Дерево успешно построено\n");

    return EXIT_SUCCESS;
}

int exec_add(binary_tree_t *tree)
{
    int rc = 0;

    char c;

    fflush(stdin);
    if (scanf("%c", &c) != 1 || !isalpha(c))
    {
        printf("\n\t ! Элемент должен быть буквой.\n");
        return 0;
    }
    fflush(stdin);

    if ((rc = scapegoat_add(&(tree->root), c, NULL, 1)))
        return rc;

    printf("\t < Буква успешно добавлена.\n");

    return EXIT_SUCCESS;
}

void exec_del(binary_tree_t *tree)
{
    char c;

    fflush(stdin);
    if (scanf("%c", &c) != 1 || !isalpha(c))
    {
        printf("\n\t ! Элемент должен быть буквой.\n");
        return;
    }
    fflush(stdin);

    scapegoat_del(&(tree->root), c);

    printf("\t < Буква успешно удалена.\n");
}

void exec_print_unique_postfix(binary_tree_t *tree)
{
    scapegoat_del_ununique(&(tree->root));

    printf("\t < Элементы дерева: ");
    scapegoat_print_postfix(tree->root);
    printf("\n");
}

void exec_time_cmp_del_ununique()
{
    printf("Время замеряется сто раз и высчитывается среднее значение \n\n");
    printf("Размер\tСтрока, нс\tДерево, нс\n");
    FILE *f = fopen("dataset.txt", "r");
    my_string_t s;
    for (size_t i = 1; i <= 13; i++)
    {
        string_scan(s, STR_LEN, f);

        printf("%zu\t\t%llu\t\t%llu\n", strlen(s), string_del_ununique_time(s), scapegoat_del_ununique_time(s));
    }

    fclose(f);

    printf("\n");
}

void exec_time_cmp_del()
{
    printf("Вычисляется среднее время удаления случайного элемента из дерева \n");
    printf("Замеры выполняются %d раз и высчитывается среднее значение \n\n", TIME_RUNS);
    printf("\t\tУдаление\n\n");
    printf("Размер\tВремя, нс\n");
    FILE *f = fopen("dataset.txt", "r");
    my_string_t s;
    for (size_t i = 1; i <= 11; i++)
    {
        string_scan(s, STR_LEN, f);

        printf("%zu\t\t%llu\n", strlen(s), scapegoat_del_time(s));
    }

    fclose(f);

    printf("\n");
}

void exec_time_cmp_find()
{
    printf("Вычисляется среднее время удаления случайного элемента из дерева \n");
    printf("Замеры выполняются %d раз и высчитывается среднее значение \n\n", TIME_RUNS);
    printf("\t\tПоиск\n\n");
    printf("Размер\tВремя, нс\n");
    FILE *f = fopen("dataset.txt", "r");
    my_string_t s;
    for (size_t i = 1; i <= 11; i++)
    {
        string_scan(s, STR_LEN, f);

        printf("%zu\t\t%llu\n", strlen(s), scapegoat_find_time(s));
    }

    fclose(f);

    printf("\n");
}

void exec_time_cmp_add()
{
    printf("Вычисляется среднее время добавления случайного элемента в дерево \n");
    printf("Замеры выполняются %d раз и высчитывается среднее значение \n\n", TIME_RUNS);
    printf("\t\tДобавление\n\n");
    printf("Размер\tВремя, нс\n");
    FILE *f = fopen("dataset.txt", "r");
    my_string_t s;
    for (size_t i = 1; i <= 11; i++)
    {
        string_scan(s, STR_LEN, f);

        printf("%zu\t\t%llu\n", strlen(s), scapegoat_add_time(s));
    }

    fclose(f);

    printf("\n");
}

void exec_mem_cmp()
{
    printf("Строка\n");
    printf("1000 элементов - %zu | Дополнительная память при удалении - %zu\n", sizeof(char) * STR_LEN, sizeof(char) * ALPHABET_SIZE);

    printf("\n");

    printf("Дерево\n");
    size_t mem_1_elem = sizeof(char) + sizeof(size_t) + sizeof(size_t) + sizeof(node_t *) + sizeof(node_t *);
    printf("1 элемент - %zu | 1000 элементов - %zu | Дополнительная память при удалении (Худший случай) - %zu | Структура - %zu\n", mem_1_elem, mem_1_elem * 1000, sizeof(node_t *) * 1000 + sizeof(size_t), sizeof(binary_tree_t));

    printf("\n");
}
