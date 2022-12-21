#include "actions.h"

void info_print()
{
    printf("+____________________________________________________________________________________________+\n");
    printf("| Программа позволяет выполнять операции над графом:                                         |\n");
    printf("| Возможности:                                                                               |\n"); 
    printf("|           Задать граф.                                                                     |\n"); 
    printf("|           Вывести граф в графическом виде                                                  |\n"); 
    printf("|           Вывести граф, отметить вершины, к которым от                                     |\n"); 
    printf("|             заданной вершины можно добраться по пути не длиннее А.                         |\n"); 
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
    printf("|> %*d - %-s\n", COMMAND_NUMBER_LEN, com, "Построить граф."), com++;
    // 2
    printf("|> %*d - %-s\n", COMMAND_NUMBER_LEN, com, "Вывести граф в графическом виде."), com++;
    // 3
    printf("|> %*d - %-s\n", COMMAND_NUMBER_LEN, com, "Вывести граф, отметить вершины, к которым от заданной вершины можно добраться по пути не длиннее А."), com++;

    printf("\n");

    return com - 1;
}

int actions_handler(int com, adjacency_matrix_t *matrix)
{
    switch (com)
    {
    case 0:
        break;
    case 1:
        exec_scan(matrix);
        break;
    case 2:
        adjacency_matrix_to_dot(matrix);
        printf("\t < Чтобы посмотреть граф выполните команду \"dot -Tpng graph.gv > graph.png\"\n");
        break;
    case 3:
        exec_print_paths_le(matrix);
        break;
    default:
        break;
    }

    return EXIT_SUCCESS;
}

void exec_scan(adjacency_matrix_t *matrix)
{
    if (matrix->data != NULL)
        adjacency_matrix_free(matrix);

    printf("Введите количество вершин: ");
    if (scanf("%zu", &(matrix->size)) != 1 || matrix->size < 1)
    {
        printf("\t ! Количество вершин должно быть положительным числом\n");
        return;
    }
    fflush(stdin);        

    adjacency_matrix_create(matrix, matrix->size);
    adjacency_matrix_fill_max(matrix);

    int from, to, cost;
    printf("Введите описание ребра (откуда куда стоимость): ");
    while (scanf("%d%d%d", &from, &to, &cost) == 3){
        fflush(stdin);
        adjacency_matrix_add(matrix, from - 1, to - 1, cost);
        printf("Введите описание ребра (откуда куда стоимость): ");
    }
    
    printf("\t < Граф успешно построен\n");
}

void exec_print_paths_le(adjacency_matrix_t *matrix)
{
    int from;
    printf("Введите начальную вершину: ");
    fflush(stdin);
    if (scanf("%d", &from) != 1 || from < 1 || (size_t)from > matrix->size)
        printf("\t ! Вершина должна содержаться в графе\n");

    int max_cost;
    printf("Введите A: ");
    if (scanf("%d", &max_cost) != 1)
        printf("\t ! А должно быть числом\n");
    fflush(stdin);

    adjacency_matrix_paths_le_to_dot(matrix, from - 1, max_cost);

    printf("\t < Чтобы посмотреть граф выполните команду \"dot -Tpng graph.gv > graph.png\"\n");
}