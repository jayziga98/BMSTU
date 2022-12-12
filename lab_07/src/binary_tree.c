#include "binary_tree.h"

void btree_init(binary_tree_t *tree)
{
    tree->root = NULL;
}

int btree_create_node(btree_node_t *root, btree_node_t **node, char elem)
{
    *node = malloc(sizeof(btree_node_t));
    if (*node == NULL)
    {
        btree_clear(root);
        return EXIT_BINARY_TREE_CREATE_NODE_MALLOC_ERROR;
    }

    (*node)->data = elem;
    (*node)->left = NULL;
    (*node)->right = NULL;
    (*node)->cnt = 0;

    return EXIT_SUCCESS;
}

void btree_clear(btree_node_t *root)
{
    if (root == NULL)
        return;

    btree_clear(root->left);
    btree_clear(root->right);
    free(root);
}

int btree_add(btree_node_t **root, char elem, size_t *cnt)
{
    int rc = 0;

    btree_node_t **dst = btree_find(root, elem);

    if (*dst == NULL && (rc = btree_create_node(*dst, dst, elem)))
        return rc;

    if (cnt == NULL)
        (*dst)->cnt++;
    else
        (*dst)->cnt = *cnt;

    return EXIT_SUCCESS;
}

void btree_del(btree_node_t **root, char elem)
{
    if ((*root) == NULL)
        return;

    btree_node_t **dst = btree_find(root, elem);

    if ((*dst) == NULL)
        return;

    btree_node_t *temp = *dst;
    if ((*dst)->left == NULL && (*dst)->right == NULL)
        *dst = NULL;
    else if ((*dst)->left != NULL && (*dst)->right != NULL)
    {
        btree_node_t *parent = (*dst);
        *dst = btree_rightmost_son((*dst)->left, &parent);   
        if ((*dst)->left != NULL)
        {
            parent = *dst;
            *dst = (*dst)->left;
            parent->left = NULL;
        }
        (*dst)->right = temp->right;
        if (parent != temp)
        {
            (*dst)->left = temp->left;
            parent->right = NULL;
        }
        else
            parent->left = NULL;
    }
    else if ((*dst)->left != NULL)
        *dst = (*dst)->left;
    else if ((*dst)->right != NULL)
        *dst = (*dst)->right;

    free(temp); 
}

btree_node_t *btree_rightmost_son(btree_node_t *root, btree_node_t **parent)
{
    if (root->right == NULL)
        return root;

    *parent = root;
    return btree_rightmost_son(root->right, parent);
}

btree_node_t **btree_find(btree_node_t **root, char elem)
{
    if ((*root) == NULL || (*root)->data == elem)
        return root;

    if (elem > (*root)->data)
        return btree_find(&((*root)->right), elem);
    else
        return btree_find(&((*root)->left), elem);
}

size_t btree_height(btree_node_t *root)
{
    if (root == NULL)
        return 0;
    if (root->left == NULL && root->right == NULL)
        return 1;

    size_t left_h = btree_height(root->left);
    size_t right_h = btree_height(root->right);

    if (right_h > left_h)
        return right_h + 1;

    return left_h + 1;
}

void btree_del_ununique(btree_node_t **root)
{
    if ((*root) == NULL)
        return;

    btree_del_ununique(&((*root)->right));
    btree_del_ununique(&((*root)->left));
    if ((*root)->cnt > 1)
        btree_del(root, (*root)->data);
}

void btree_get_level(btree_node_t *root, size_t lvl, int left, int right, btree_nodes_t *nodes)
{
    if (root == NULL)
    {
        if (lvl == 0)
            nodes->data[left].data = ' ';
        return;
    }

    if (lvl == 0)
    {
        nodes->data[left] = *root;
        //printf("\n%c %d\n", root->data, ind);
    }
    else
    {
        btree_get_level(root->left, lvl - 1, left, (left + right) / 2, nodes);
        btree_get_level(root->right, lvl - 1, (left + right) / 2, right, nodes);
    }
}


void btree_print_tree(btree_node_t *root)
{
    if (root == NULL)
        return;

    FILE *f = fopen("tempbtree.txt", "w+");

    printf("\n");
    size_t h = btree_height(root);
    if (h >= 6)
    {
        fclose(f);
        printf("Дерево слишком большое!\n");
        return;
    }

    size_t elems = 1;
    int spacing = 1;
    for (size_t i = 0; i <= h; i++)
        spacing *= 2;

    for (size_t i = 0; i < h; i++, elems *= 2, spacing /= 2)
    {
        btree_nodes_t level;
        level.size = elems;
        level.data = malloc(elems * sizeof(btree_node_t));
        for (size_t i = 0; i < elems; i++)
            level.data[i].data = ' ';
        if (i == 0)
            btree_get_level(root, i, 0, elems, &level);
        else
            btree_get_level(root, i, 0, elems, &level);

        if (i == 0)
        {
            if (level.data[0].cnt > 1)
                printf(ANSI_COLOR_GREEN"%*c\n"ANSI_COLOR_RESET, spacing, level.data[0].data), fprintf(f, "%*c\n", spacing, level.data[0].data);
            else
                printf("%*c\n", spacing, level.data[0].data), fprintf(f, "%*c\n", spacing, level.data[0].data);
        }
        else
        {
            for (size_t childs = 0; childs < level.size; childs += 2)
            {
                for (int first = 0; first < spacing - 2; first++)
                    if (level.data[childs].data != ' ')
                    {
                        if (first == 0)
                            printf("%*c", spacing, '.'), fprintf(f, "%*c", spacing, '.');
                        printf(first == spacing - 3 ? "/" : "_"), fprintf(f, first == spacing - 3 ? "/" : "_");
                    }
                    else
                    {
                        if (first == 0)
                            printf("%*c", spacing, ' '), fprintf(f, "%*c", spacing, ' ');
                        printf(" "), fprintf(f, " ");
                    }
                printf("   "), fprintf(f, "   ");
                for (int first = 0; first < spacing - 2; first++)
                    if (level.data[childs + 1].data != ' ')
                    {
                        printf(first == 0 ? "\\" : "_"), fprintf(f, first == 0 ? "\\" : "_");
                        if (first + 1 == spacing - 2)
                            printf("%c", '.'), fprintf(f, "%c", '.');
                    }
                    else
                    {
                        if (first + 1 == spacing - 2)
                            printf("%c", ' '), fprintf(f, "%c", ' ');
                        printf(" "), fprintf(f, " ");
                    }

                printf("%*c", spacing, ' '), fprintf(f, "%*c", spacing, ' ');
            }
            printf("\n"), fprintf(f, "\n");;
            for (size_t childs = 0; childs < level.size; childs += 2)
            {
                if (level.data[childs].cnt > 1)
                    printf(ANSI_COLOR_GREEN"%*c"ANSI_COLOR_RESET, spacing, level.data[childs].data), fprintf(f, "%*c", spacing, level.data[childs].data);
                else
                    printf("%*c", spacing, level.data[childs].data), fprintf(f, "%*c", spacing, level.data[childs].data);
                
                if (level.data[childs + 1].cnt > 1)
                    printf(ANSI_COLOR_GREEN"%*c"ANSI_COLOR_RESET, spacing * 2, level.data[childs + 1].data), fprintf(f, "%*c", spacing * 2, level.data[childs + 1].data);
                else
                    printf("%*c", spacing * 2, level.data[childs + 1].data), fprintf(f, "%*c", spacing * 2, level.data[childs + 1].data);

                printf("%*c", spacing, ' '), fprintf(f, "%*c", spacing, ' ');
            }
            printf("\n"), fprintf(f, "\n");
        }
        free(level.data);
    }

    fclose(f);
}

void btree_print_postfix(btree_node_t *root)
{
    if (root == NULL)
        return;

    btree_print_postfix(root->left);
    btree_print_postfix(root->right);
    printf("%c ", root->data);
}

unsigned long long btree_del_ununique_time(my_string_t s)
{
    unsigned long long sum = 0;

    for (int i = 0; i < TIME_RUNS; i++)
    {
        struct timespec beg, end;

        binary_tree_t tree;
        btree_init(&tree);

        for (size_t j = 0; s[j] != '\0'; j++)
            btree_add(&(tree.root), s[j], NULL);

        clock_gettime(CLOCK_MONOTONIC_RAW, &beg);   
        btree_del_ununique(&(tree.root));
        clock_gettime(CLOCK_MONOTONIC_RAW, &end);

        btree_clear(tree.root);

        sum += nanoseconds(&beg, &end);
    }

    return sum / TIME_RUNS;
}

int btree_scan_from(binary_tree_t *tree, my_string_t s)
{
    int rc = 0;

    btree_init(tree);

    for (size_t i = 0; s[i] != '\0'; i++)
        if (isalpha(s[i]))
            if ((rc = btree_add(&(tree->root), s[i], NULL)))
                return rc;

    return EXIT_SUCCESS;
}

unsigned long long btree_add_time(my_string_t s)
{
    unsigned long long sum = 0;

    for (int i = 0; i < TIME_RUNS; i++)
    {
        my_string_t copy;
        strcpy(copy, s);


        binary_tree_t tree;
        btree_init(&tree);

        int cnt = 0;

        unsigned long long avg = 0;
        while (copy[0] != '\0')
        {
            struct timespec beg, end;

            char c = string_del_rand(copy);

            clock_gettime(CLOCK_MONOTONIC_RAW, &beg); 
            btree_add(&(tree.root), c, NULL);  
            clock_gettime(CLOCK_MONOTONIC_RAW, &end);

            avg += nanoseconds(&beg, &end);
            cnt++;
        }

        btree_clear(tree.root);

        sum += avg / cnt;
    }

    return sum / TIME_RUNS;
}

unsigned long long btree_del_time(my_string_t s)
{
    unsigned long long sum = 0;

    for (int i = 0; i < TIME_RUNS; i++)
    {
        my_string_t copy;
        strcpy(copy, s);

        binary_tree_t tree;
        btree_init(&tree);
        for (size_t j = 0; copy[j] != '\0'; j++)
            btree_add(&(tree.root), copy[j], NULL);

        int cnt = 0;;

        unsigned long long avg = 0;
        while (copy[0] != '\0')
        {
            struct timespec beg, end;

            char c = string_del_rand(copy);

            clock_gettime(CLOCK_MONOTONIC_RAW, &beg); 
            btree_del(&(tree.root), c); 
            clock_gettime(CLOCK_MONOTONIC_RAW, &end);

            avg += nanoseconds(&beg, &end);
            cnt++;
        }

        btree_clear(tree.root);

        sum += avg / cnt;
    }

    return sum / TIME_RUNS;
}

unsigned long long btree_find_time(my_string_t s)
{
    unsigned long long sum = 0;

    for (int i = 0; i < TIME_RUNS; i++)
    {
        my_string_t copy;
        strcpy(copy, s);

        binary_tree_t tree;
        btree_init(&tree);
        for (size_t j = 0; copy[j] != '\0'; j++)
            btree_add(&(tree.root), copy[j], NULL);

        int cnt = 0;;

        unsigned long long avg = 0;
        while (copy[0] != '\0')
        {
            struct timespec beg, end;

            char c = string_del_rand(copy);

            clock_gettime(CLOCK_MONOTONIC_RAW, &beg); 
            btree_find(&(tree.root), c); 
            clock_gettime(CLOCK_MONOTONIC_RAW, &end);

            avg += nanoseconds(&beg, &end);
            cnt++;
        }

        btree_clear(tree.root);

        sum += avg / cnt;
    }

    return sum / TIME_RUNS;
}

size_t btree_elem_mem()
{
    return sizeof(btree_node_t);
}

size_t btree_struct_mem()
{
    return sizeof(binary_tree_t);
}