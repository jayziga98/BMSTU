#include <stdio.h>
#include <stdlib.h>

#include "actions.h"

int main()
{
    adjacency_matrix_t graph;
    adjacency_matrix_init(&graph);

    info_print();    

    int max_com;
    for (int com = -1, com_cnt = 0; com != 0; com_cnt++, com_cnt %= 3)
    {
        if (!com_cnt)
            max_com = actions_print();

        int rc = 0;

        printf("\n > Выполнить команду №: ");
        fflush(stdin);
        if (scanf("%d", &com) == 1)
        {
            printf("\n");

            rc = actions_handler(com, &graph);

            if (rc)
                return EXIT_FAILURE;
        }
        else
            printf("\n\t ? Введите цифру от 0 до %d\n", max_com);
    }

    adjacency_matrix_free(&graph);

    return EXIT_SUCCESS;
}