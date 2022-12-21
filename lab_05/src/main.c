#include <stdio.h>
#include <stdlib.h>

#include "actions.h"

int main()
{
    queue_linked_list_t qll;
    queue_linked_list_init(&qll);

    queue_std_t q;

    queuing_system_t qsys;
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

            rc = actions_handler(com, &qsys, &q, &qll);

            if (rc)
                return EXIT_FAILURE;
        }
        else
            printf("\n\t ? Введите цифру от 0 до %d\n", max_com);
    }

    return EXIT_SUCCESS;
}
