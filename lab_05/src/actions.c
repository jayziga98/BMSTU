#include "actions.h"

void info_print()
{
    printf("+____________________________________________________________________________________________+\n");
    printf("| Программа позволяет работать со структурой данных под названием очередь                    |\n");
    printf("| Можно смоделировать процеес обслуживания до ухода из системы первых 1000 заявок,           |\n");
    printf("|       выдавая после обслуживания каждых 100 заявок информацию о текущей                    |\n");
    printf("|       и средней длине очереди                                                              |\n"); 
    printf("|                                                                                            |\n"); 
    printf("| По требованию можно получать адреса элементов очереди при удалении и добавлении элементов. |\n");   
    printf("|       (Только для реализации на связном списке)                                            |\n");   
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
    printf("|> %*d - %-s\n", COMMAND_NUMBER_LEN, com, "Смоделировать [Классическая очередь]."), com++;
    // 2
    printf("|> %*d - %-s\n", COMMAND_NUMBER_LEN, com, "Смоделировать [Очередь на связном списке]."), com++;

    printf("|\n");

    // 3
    printf("|> %*d - %-s\n", COMMAND_NUMBER_LEN, com, "Сравнить эффективность."), com++;
    // 4
    printf("|> %*d - %-s\n", COMMAND_NUMBER_LEN, com, "Сравнить объем занятой памяти."), com++;

    printf("\n");

    return com - 1;
}

int actions_handler(int com, queuing_system_t *qsys, queue_std_t *q, queue_linked_list_t *qll)
{
    switch (com)
    {
    case 0:
        break;
    case 1:
        exec_simulate(1, qsys, q, qll);
        break;
    case 2:
        exec_simulate(2, qsys, q, qll);
        break;
    case 3:
        exec_time_cmp();
        break;
    case 4:
        exec_mem_cmp();
        break;
    default:
        break;
    }

    return EXIT_SUCCESS;
}

void exec_simulate(int type, queuing_system_t *qsys, queue_std_t *q, queue_linked_list_t *qll)
{
    int addrs = 0;

    char ask;
    fflush(stdin);
    printf("\n\t ? Выводить адреса [Y\\n]: ");
    if (scanf("%c", &ask) == 1 && ask != 'n')
        addrs = 1;

    if (addrs)
    {
        FILE *f = fopen("addrs.txt", "w");
        fclose(f);
    }

    if (type == 1)
        qsystem_simulate(qsys, addrs, q, queuestd_create, queuestd_add, queuestd_pop, queuestd_clear, REQS_OUT, 1);
    else if (type == 2)
        qsystem_simulate(qsys, addrs, qll, NULL, queue_linked_list_add, queue_linked_list_pop, queue_linked_list_clear, REQS_OUT, 1);

    printf("\n");
    printf("\t < Общее время выполнения     | %lf\n", qsys->exec_time);
    printf("\t < Количество вошедших заявок | %zu\n", qsys->cnt_req_in);
    printf("\t < Количество вышедших заявок | %zu\n", qsys->cnt_req_out);
    printf("\t < Количество срабатываний ОА | %d\n", qsys->unit.runs);
    printf("\t < Время простоя ОА           | %lf\n", qsys->exec_time - qsys->unit.exec_time);
}

void exec_time_cmp()
{
    printf("Время замеряется сто раз и высчитывается среднее значение \n");
    printf("\t < Очередь на массиве, нс      : %llu\n", qsystem_simulate_time(1));
    printf("\t < Очередь на связном списке нс: %llu\n", qsystem_simulate_time(2));

    printf("Время добавления и удаления\n");
    printf("\t < Массив\n");
    queuestd_add_time();
    printf("\t < Связный список\n");
    queue_linked_list_add_time();

    printf("\n");
}

void exec_mem_cmp()
{
    printf("Очередь на массиве\n");
    printf("Структура: %10zu| Одна запись: %10zu| 1 запись + Структура: %10zu| 1000 записей + Структура: %10zu|\n", sizeof(queue_std_t), sizeof(int), sizeof(queue_std_t) + sizeof(int),sizeof(queue_std_t) + sizeof(int) * 1000);

    printf("\n");

    printf("Очередь на связном списке\n");
    printf("Структура: %10zu| Одна запись: %10zu| 1 запись + Структура: %10zu| 3 записи + Структура    : %10zu|\n", sizeof(queue_linked_list_t), sizeof(node_t), sizeof(queue_linked_list_t) + sizeof(node_t), sizeof(queue_linked_list_t) + sizeof(node_t) * 3);

    printf("\n");

    printf("3 записи выбрано с расчетом на то что средняя длина очереди равна 3 записям\n");
    printf("в случае с реализацией на массиве объем полезных данных не влияет на итоговый объем занятой памяти\n");
}
