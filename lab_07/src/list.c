#include "list.h"

int list_empty(list_t *list)
{
    return !(list->head);
}

void list_init(list_t *list)
{
    list->head = NULL;
    list->size = 0;
}

int list_add(list_t *list, hash_table_open_data_t *elem)
{
    node_t *new = malloc(sizeof(node_t));
    if (new == NULL)
        return EXIT_ALLOCATING_NODE_ERROR;

    new->data.letter = elem->letter;

    if (elem->count == 0)
        new->data.count = 1;
    else    
        new->data.count = elem->count;

    new->next = list->head;
    list->head = new;

    list->size++;

    return EXIT_SUCCESS;
}

int list_pop(list_t *list, hash_table_open_data_t *last)
{
    if (list_empty(list))
        return EXIT_EMPTY_LIST_ERROR;

    node_t *temp = list->head;
    
    list->head = temp->next;

    if (last != NULL)
            *last = temp->data;

    free(temp);

    list->size--;

    return EXIT_SUCCESS;
}

void list_del_by(list_t *list, hash_table_open_data_t *elem)
{
    if (list_empty(list))
        return;

    if (elem == NULL)
        return;

    for (node_t *cur_node = list->head; cur_node != NULL; cur_node = cur_node->next)
        if (cur_node->next != NULL && cur_node->next->data.letter == elem->letter)
        {
            node_t *temp = cur_node->next;
            
            cur_node->next = temp->next;
            cur_node = temp->next;

            *elem = temp->data;

            free(temp);

            break;
        }
        else if (cur_node->data.letter == elem->letter)
        {
            node_t *temp = cur_node;
            
            *elem = temp->data;

            free(temp);

            list_init(list);

            break;
        }

    list->size--;
}

void list_del_ununique(list_t *list)
{
    if (list_empty(list))
        return;

    for (node_t *cur_node = list->head; cur_node != NULL; cur_node = cur_node->next)
        if (cur_node->next != NULL && cur_node->next->data.count > 1)
        {
            node_t *temp = cur_node->next;
            
            cur_node->next = temp->next;
            cur_node = temp->next;

            free(temp);

            break;
        }
        else if (cur_node->data.count > 1)
        {
            node_t *temp = cur_node;

            free(temp);

            list_init(list);

            break;
        }

    list->size--;
}

void list_add_by(list_t *list, hash_table_open_data_t *elem)
{
    if (elem == NULL)
        return;

    int flag = 1;
    for (node_t *cur_node = list->head; flag && cur_node != NULL; cur_node = cur_node->next)
        if (cur_node->data.letter == elem->letter)
        {
            cur_node->data.count++;
            flag = 0;
        }

    if (flag)
        list_add(list, elem);
}

size_t list_count(list_t *list, char elem)
{
    if (list_empty(list))
        return 0;

    for (node_t *cur_node = list->head; cur_node != NULL; cur_node = cur_node->next)
        if (cur_node->data.letter == elem)
            return cur_node->data.count;

    return 0;
}

int list_clear(list_t *list)
{
    if (list_empty(list))
        return EXIT_SUCCESS;

    int rc = 0;

    while (!list_empty(list))
        if ((rc = list_pop(list, NULL)))
            return rc;

    return EXIT_SUCCESS;
}

void list_print(list_t *list, char sep, char end)
{
    if (list_empty(list))
        return;

    for (node_t *cur_node = list->head; cur_node != NULL; cur_node = cur_node->next)
    if (cur_node->data.count == 1)
    {
        if (cur_node->next == NULL)
            printf("%c, %zu", cur_node->data.letter, cur_node->data.count);
        else
            printf("%c, %zu%c", cur_node->data.letter, cur_node->data.count, sep);
    }
    else
    {
        if (cur_node->next == NULL)
            printf(ANSI_COLOR_GREEN"%c, %zu"ANSI_COLOR_RESET, cur_node->data.letter, cur_node->data.count);
        else
            printf(ANSI_COLOR_GREEN"%c, %zu%c"ANSI_COLOR_RESET, cur_node->data.letter, cur_node->data.count, sep);
    }
    printf("%c", end);
}

size_t list_mem(list_t *list)
{
    size_t mem = 0;

    mem += sizeof(node_t) * list->size;

    mem += sizeof(list_t);

    return mem;
}
