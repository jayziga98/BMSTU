#include <stdio.h>
#include <stdlib.h>

#include "binary_tree.h"
#include "actions.h"

int main()
{
    binary_tree_t btree;
    btree.root = NULL;
    scapegoat_tree_t stree;
    stree.root = NULL;
    hash_table_open_t table_open;
    table_open.data = NULL;
    hash_table_close_t table_close;
    table_close.data = NULL;

    info_print();    

    int max_com;
    for (int com = -1, com_cnt = 0; com != 0; com_cnt++, com_cnt %= 3)
    {
        if (!com_cnt)
            max_com = actions_print();

        int rc = 0;

        printf("\n > Выполнить команду №: ");
        if (scanf("%d", &com) == 1)
        {
            flush_stdin();
            printf("\n");

            rc = actions_handler(com, &table_open, &table_close, &stree, &btree);

            if (rc)
                return EXIT_FAILURE;
        }
        else
            printf("\n\t ? Введите цифру от 0 до %d\n", max_com);
    }

    btree_clear(btree.root);
    scapegoat_clear(stree.root);
    hashtableopen_clear(&table_open);
    hashtableclose_clear(&table_close);

    return EXIT_SUCCESS;
}