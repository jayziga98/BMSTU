#include "scapegoat_tree.h"

void scapegoat_init(binary_tree_t *tree)
{
    tree->root = NULL;
}

int scapegoat_create_node(node_t *root, node_t **node, char elem)
{
    *node = malloc(sizeof(node_t));
    if (*node == NULL)
    {
        scapegoat_clear(root);
        return EXIT_SCAPEGOAT_TREE_CREATE_NODE_MALLOC_ERROR;
    }

    (*node)->data = elem;
    (*node)->left = NULL;
    (*node)->right = NULL;
    (*node)->cnt = 0;

    return EXIT_SUCCESS;
}

void scapegoat_clear(node_t *root)
{
    if (root == NULL)
        return;

    scapegoat_clear(root->left);
    scapegoat_clear(root->right);
    free(root);
}

int scapegoat_add(node_t **root, char elem, size_t *cnt, int balance)
{
    int rc = 0;

    node_t **dst = scapegoat_find(root, elem);

    if (*dst == NULL && (rc = scapegoat_create_node(*dst, dst, elem)))
        return rc;

    if (cnt == NULL)
        (*dst)->cnt++;
    else
        (*dst)->cnt = *cnt;

    if (balance)
        scapegoat_balance(root);

    return EXIT_SUCCESS;
}

void scapegoat_del(node_t **root, char elem)
{
    if ((*root) == NULL)
        return;

    node_t **dst = scapegoat_find(root, elem);

    if ((*dst) == NULL)
        return;

    node_t *temp = *dst;
    if ((*dst)->left == NULL && (*dst)->right == NULL)
        *dst = NULL;
    else if ((*dst)->left != NULL && (*dst)->right != NULL)
    {
        node_t *parent = (*dst);
        *dst = scapegoat_rightmost_son((*dst)->left, &parent);   
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

    scapegoat_balance(root);

    free(temp); 
}

node_t *scapegoat_rightmost_son(node_t *root, node_t **parent)
{
    if (root->right == NULL)
        return root;

    *parent = root;
    return scapegoat_rightmost_son(root->right, parent);
}

node_t **scapegoat_find(node_t **root, char elem)
{
    if ((*root) == NULL || (*root)->data == elem)
        return root;

    if (elem > (*root)->data)
        return scapegoat_find(&((*root)->right), elem);
    else
        return scapegoat_find(&((*root)->left), elem);
}

size_t scapegoat_height(node_t *root)
{
    if (root == NULL)
        return 0;
    if (root->left == NULL && root->right == NULL)
        return 1;

    size_t left_h = scapegoat_height(root->left);
    size_t right_h = scapegoat_height(root->right);

    if (right_h > left_h)
        return right_h + 1;

    return left_h + 1;
}

// del subtree and return array of nodes data
void scapegoat_flatten_inorder(node_t **root, nodes_t *ptrs)
{
    if ((*root) == NULL)
        return;

    scapegoat_flatten_inorder(&((*root)->left), ptrs);
    ptrs->size++;
    ptrs->data[ptrs->size - 1] = **root;
    scapegoat_flatten_inorder(&((*root)->right), ptrs);
    scapegoat_del(root, (*root)->data);
}

void scapegoat_build_balanced(node_t **root, nodes_t *ptrs, size_t l, size_t r)
{
    if (l >= r)
        return;
    

    scapegoat_add(root, ptrs->data[(r + l) / 2].data, &(ptrs->data[(r + l) / 2].cnt), 0);
    if (r - l == 1)
    {
        scapegoat_add(root, ptrs->data[l].data, &(ptrs->data[l].cnt), 0);
        return;
    }
    else if (r - l == 2)
    {
        scapegoat_add(root, ptrs->data[l + 1].data, &(ptrs->data[l + 1].cnt), 0);
        scapegoat_add(root, ptrs->data[l].data, &(ptrs->data[l].cnt), 0);
        return;
    }

    scapegoat_build_balanced(&((*root)->right), ptrs, (r + l) / 2 + 1, r);
    scapegoat_build_balanced(&((*root)->left), ptrs, l, (r + l) / 2);
}

void scapegoat_balance(node_t **root)
{
    node_t **scapegoat = NULL;
    scapegoat_find_scapegoat(root, &scapegoat);
    if (scapegoat == NULL)
        return;

    nodes_t ptrs;
    ptrs.size = 0;
    ptrs.data = malloc(sizeof(node_t) * ((*scapegoat)->weight + 1));
    scapegoat_flatten_inorder(scapegoat, &ptrs);
    scapegoat_build_balanced(scapegoat, &ptrs, 0, ptrs.size);

    //printf("\nSIZE: %zu\n", ptrs.size);
    free(ptrs.data);
}

// fills node.weight of all nodes
// returns root weight and ptr to scapegoat node
size_t scapegoat_find_scapegoat(node_t **root, node_t ***scapegoat)
{
    if ((*root) == NULL)  
        return 0;

    size_t left_w = scapegoat_find_scapegoat(&((*root)->left), scapegoat);
    size_t right_w = scapegoat_find_scapegoat(&((*root)->right), scapegoat);

    if (((left_w >= right_w && left_w - right_w > 1) || (left_w <= right_w && right_w - left_w > 1)))
        *scapegoat = root;

    (*root)->weight = left_w + right_w;

    return (*root)->weight + 1;
}

void scapegoat_del_ununique(node_t **root)
{
    if ((*root) == NULL)
        return;

    scapegoat_del_ununique(&((*root)->right));
    scapegoat_del_ununique(&((*root)->left));
    if ((*root)->cnt > 1)
        scapegoat_del(root, (*root)->data);

    scapegoat_balance(root);
}

void scapegoat_print_level(node_t *root, size_t lvl, nodes_t *nodes)
{
    if (root == NULL)
    {
        if (lvl == 0)
            nodes->size++, nodes->data[nodes->size - 1].data = ' ';
        return;
    }

    if (lvl == 0)
        nodes->size++, nodes->data[nodes->size - 1] = *root;
    else
    {
        scapegoat_print_level(root->left, lvl - 1, nodes);
        scapegoat_print_level(root->right, lvl - 1, nodes);
    }
}

void scapegoat_print_tree(node_t *root)
{
    if (root == NULL)
        return;

    FILE *f = fopen("temp.txt", "w+");

    printf("\n");
    size_t h = scapegoat_height(root);

    size_t elems = 1;
    int spacing = 1;
    for (size_t i = 0; i <= h; i++)
        spacing *= 2;

    for (size_t i = 0; i < h; i++, elems *= 2, spacing /= 2)
    {
        nodes_t level;
        level.size = 0;
        level.data = malloc(sizeof(node_t) * elems);
        scapegoat_print_level(root, i, &level);

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

void scapegoat_print_postfix(node_t *root)
{
    if (root == NULL)
        return;

    scapegoat_print_postfix(root->left);
    scapegoat_print_postfix(root->right);
    printf("%c ", root->data);
}

void scapegoat_print_prefix(node_t *root)
{
    if (root == NULL)
        return;

    printf("%c ", root->data);
    scapegoat_print_prefix(root->left);
    scapegoat_print_prefix(root->right);
}

void scapegoat_print_infix(node_t *root)
{
    if (root == NULL)
        return;

    scapegoat_print_infix(root->left);
    printf("%c ", root->data);
    scapegoat_print_infix(root->right);
}

unsigned long long scapegoat_del_ununique_time(my_string_t s)
{
    unsigned long long sum = 0;

    for (int i = 0; i < TIME_RUNS; i++)
    {
        struct timespec beg, end;

        binary_tree_t tree;
        scapegoat_init(&tree);

        for (size_t j = 0; s[j] != '\0'; j++)
            scapegoat_add(&(tree.root), s[j], NULL, 0);
        scapegoat_balance(&(tree.root));

        clock_gettime(CLOCK_MONOTONIC_RAW, &beg);   
        scapegoat_del_ununique(&(tree.root));
        clock_gettime(CLOCK_MONOTONIC_RAW, &end);

        scapegoat_clear(tree.root);

        sum += nanoseconds(&beg, &end);
    }

    return sum / TIME_RUNS;
}

unsigned long long scapegoat_find_time(my_string_t s)
{
    unsigned long long sum = 0;

    for (int i = 0; i < TIME_RUNS; i++)
    {
        my_string_t copy;
        strcpy(copy, s);

        binary_tree_t tree;
        scapegoat_init(&tree);
        for (size_t j = 0; copy[j] != '\0'; j++)
            scapegoat_add(&(tree.root), copy[j], NULL, 0);
        scapegoat_balance(&(tree.root));

        int cnt = 0;;

        unsigned long long avg = 0;
        while (copy[0] != '\0')
        {
            struct timespec beg, end;

            char c = string_del_rand(copy);

            clock_gettime(CLOCK_MONOTONIC_RAW, &beg); 
            scapegoat_find(&(tree.root), c); 
            clock_gettime(CLOCK_MONOTONIC_RAW, &end);

            avg += nanoseconds(&beg, &end);
            cnt++;
        }

        scapegoat_clear(tree.root);

        sum += avg / cnt;
    }

    return sum / TIME_RUNS;
}

unsigned long long scapegoat_add_time(my_string_t s)
{
    unsigned long long sum = 0;

    for (int i = 0; i < TIME_RUNS; i++)
    {
        my_string_t copy;
        strcpy(copy, s);


        binary_tree_t tree;
        scapegoat_init(&tree);

        int cnt = 0;

        unsigned long long avg = 0;
        while (copy[0] != '\0')
        {
            struct timespec beg, end;

            char c = string_del_rand(copy);

            clock_gettime(CLOCK_MONOTONIC_RAW, &beg); 
            scapegoat_add(&(tree.root), c, NULL, 1);  
            clock_gettime(CLOCK_MONOTONIC_RAW, &end);

            avg += nanoseconds(&beg, &end);
            cnt++;
        }

        scapegoat_clear(tree.root);

        sum += avg / cnt;
    }

    return sum / TIME_RUNS;
}

unsigned long long scapegoat_del_time(my_string_t s)
{
    unsigned long long sum = 0;

    for (int i = 0; i < TIME_RUNS; i++)
    {
        my_string_t copy;
        strcpy(copy, s);

        binary_tree_t tree;
        scapegoat_init(&tree);
        for (size_t j = 0; copy[j] != '\0'; j++)
            scapegoat_add(&(tree.root), copy[j], NULL, 0);
        scapegoat_balance(&(tree.root));

        int cnt = 0;;

        unsigned long long avg = 0;
        while (copy[0] != '\0')
        {
            struct timespec beg, end;

            char c = string_del_rand(copy);

            clock_gettime(CLOCK_MONOTONIC_RAW, &beg); 
            scapegoat_del(&(tree.root), c); 
            clock_gettime(CLOCK_MONOTONIC_RAW, &end);

            avg += nanoseconds(&beg, &end);
            cnt++;
        }

        scapegoat_clear(tree.root);

        sum += avg / cnt;
    }

    return sum / TIME_RUNS;
}
