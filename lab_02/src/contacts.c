#include "../inc/contacts.h"

int contacts_scan(contacts_t *contacts, size_t n, keys_t *keys, FILE *stream)
{
    int rc = 0;

    contacts->size = 0;
    if (stream == stdin)
        for (size_t i = 0; i < n; i++)
        {
            printf("Введите абонента: ");
            contacts->size++;
            if ((rc = contact_scan(&(contacts->data[contacts->size - 1]), stream)))
                return rc;
        }
    else
    {
        for (size_t i = 0; !rc; i++)
        {
            contacts->size++;
            rc = contact_scan(&(contacts->data[contacts->size - 1]), stream);
        }

        contacts->size--;

        if (!feof(stream))
            return rc;
    }

    if ((rc = keys_init(keys, contacts)))
        return rc;

    return EXIT_SUCCESS;
}

void contacts_print(contacts_t *contacts, int formatted)
{
    for (size_t i = 0; i < contacts->size; i++)
    {
        if (formatted)
        {
            contact_print(&(contacts->data[i]), 1);
            for (size_t j = 0; j < PRINT_CONTACT_WIDTH; j++)
                printf("_");
            printf("\n");
        }
        else
            contact_print(&(contacts->data[i]), 0);
    }
}

int contacts_add(contacts_t *contacts, contact_t *contact, keys_t *keys)
{
    if (contacts->size + 1 > CONTACTS_SIZE)
        return EXIT_CONTACTS_OVERFLOW;

    contacts->size++;
    contacts->data[contacts->size - 1] = *contact;

    keys_add(keys, &(contacts->data[contacts->size - 1]));

    return EXIT_SUCCESS;
}

int keys_init(keys_t *keys, contacts_t *contacts)
{
    int rc = 0;

    keys->size = 0;
    for (size_t i = 0; i < contacts->size; i++)
        if ((rc = keys_add(keys, &(contacts->data[i]))))
            return rc;

    return EXIT_SUCCESS;
}

int keys_add(keys_t *keys, contact_t *contact)
{
    if (keys->size + 1 > CONTACTS_SIZE)
        return EXIT_KEYS_OVERFLOW;

    keys->size++;
    keys->data[keys->size - 1].source_index = keys->size - 1;
    strcpy(keys->data[keys->size - 1].surname, contact->surname);

    return EXIT_SUCCESS;
}

void swap(void *ptr1, void *ptr2, size_t size)
{
    char *cur_b1 = ptr1;
    char *cur_b2 = ptr2;
    for (size_t i = 0; i < size; i++, cur_b1++, cur_b2++)
    {
        char t = *cur_b1;
        *cur_b1 = *cur_b2;
        *cur_b2 = t;
    }
}

void contacts_del_by_pos(contacts_t *contacts, size_t pos)
{
    for (size_t i = pos; i < contacts->size - 1; i++)
        swap((void *)&(contacts->data[i]), (void *)&(contacts->data[i + 1]), sizeof(contacts->data[i]));

    if (pos < contacts->size)
        contacts->size--;
}

int contacts_del_by_key(contacts_t *contacts, char key[SURNAME_LEN], keys_t *keys, int *n)
{
    int rc = 0;

    *n = 0;
    for (size_t i = keys->size; i > 0; i--)
        if (!strcmp(key, keys->data[i - 1].surname))
        {
            contacts_del_by_pos(contacts, keys->data[i - 1].source_index);
            (*n)++;
            if ((rc = keys_init(keys, contacts)))
                return rc;
        }

    return EXIT_SUCCESS;
}

int contacts_print_by(contacts_t *contacts, contact_private_t *date, int (*predicate)(contact_t *, contact_private_t *))
{
    int cnt = 0;
    for (size_t i = 0; i < contacts->size; i++)
        if(predicate(&(contacts->data[i]), date))
        {
            contact_print(&(contacts->data[i]), 0);
            cnt++;
        }

    return cnt;
}

void contacts_print_from_keys(contacts_t *contacts, keys_t *keys, int formatted)
{
    for (size_t i = 0; i < keys->size; i++)
    {
        if (formatted)
        {
            contact_print(&(contacts->data[keys->data[i].source_index]), 1);
            for (size_t j = 0; j < PRINT_CONTACT_WIDTH; j++)
                printf("_");
            printf("\n");
        }
        else
            contact_print(&(contacts->data[keys->data[i].source_index]), 0);
    }
}

void contacts_from_keys(contacts_t *contacts, keys_t *keys, contacts_t *result)
{
    result->size = contacts->size;
    for (size_t i = 0; i < keys->size; i++)
        result->data[i] = contacts->data[keys->data[i].source_index];
}

void keys_fields_print(int formatted)
{
    if (formatted)
    {
        for (size_t j = 0; j < PRINT_INDEX_WIDTH * 2 + PRINT_SURNAME_WIDTH + 4; j++)
            printf("_");
        printf("\n");
        printf("|%*s|%*s|%*s|\n", PRINT_INDEX_WIDTH, "Index", PRINT_INDEX_WIDTH, "Source Index", PRINT_SURNAME_WIDTH, "Surname");
        for (size_t j = 0; j < PRINT_INDEX_WIDTH * 2 + PRINT_SURNAME_WIDTH + 4; j++)
            printf("_");
        printf("\n");
    }
    else
        printf("%s %s %s\n", "Index", "Source Index", "Surname");
}

void keys_print(keys_t *keys, int formatted)
{
    if (formatted)
    {
        for (size_t i = 0; i < keys->size; i++)
        {
            printf("|%-*zu|%-*d|%-*s|\n", PRINT_INDEX_WIDTH, i + 1, PRINT_INDEX_WIDTH, keys->data[i].source_index + 1, PRINT_SURNAME_WIDTH, keys->data[i].surname);
            for (size_t j = 0; j < PRINT_INDEX_WIDTH * 2 + PRINT_SURNAME_WIDTH + 4; j++)
                printf("_");
            printf("\n");
        }
    }
    else
    {
        for (size_t i = 0; i < keys->size; i++)
            printf("%zu %d %s\n", i + 1, keys->data[i].source_index + 1, keys->data[i].surname);
    }
    printf("\n");
}

int key_cmp(const void *key1, const void *key2)
{
    return strcmp(((const key_t *)key1)->surname, ((const key_t *)key2)->surname);
}

void *find_min(void *ptr_beg, void *ptr_end, size_t size, int (*comp)(const void *, const void *))
{
    if (comp == NULL)
        return NULL;

    void *mini = ptr_beg;
    for (; ptr_beg < ptr_end; ptr_beg = (char *)ptr_beg + size)
        if (comp(mini, ptr_beg) > 0)
            mini = ptr_beg;

    return mini;
}

// Сортировка выбором по возрастанию
void mysort(void *base, size_t nmemb, size_t size, int (*compar)(const void *, const void *))
{
    void *ptr_e = (char *)base + nmemb * size;
    for (void *ptr_cur = base; ptr_cur < ptr_e; ptr_cur = (char *)ptr_cur + size)
    {
        void *mini = find_min(ptr_cur, ptr_e, size, compar);
        swap(mini, ptr_cur, size);
    }
}

unsigned long long time_sort_from_keys(contacts_t *contacts, keys_t *keys, void (*sort)(void *, size_t, size_t, int (*)(const void *, const void *)))
{
    unsigned long long sum = 0;
    for (int i = 0; i < TIME_RUNS; i++)
    {
        struct timespec beg, end;

        contacts_t temp;

        clock_gettime(CLOCK_MONOTONIC_RAW, &beg);
        sort(keys->data, keys->size, sizeof(keys->data[0]), key_cmp);
        contacts_from_keys(contacts, keys, &temp);
        clock_gettime(CLOCK_MONOTONIC_RAW, &end);

        sum += nanoseconds(&beg, &end);
    }

    return sum / TIME_RUNS;
}

unsigned long long time_sort_contacts(contacts_t *contacts, void (*sort)(void *, size_t, size_t, int (*)(const void *, const void *)))
{
    unsigned long long sum = 0;
    for (int i = 0; i < TIME_RUNS; i++)
    {
        struct timespec beg, end;

        contacts_t temp = *contacts;

        clock_gettime(CLOCK_MONOTONIC_RAW, &beg);
        sort(temp.data, temp.size, sizeof(temp.data[0]), contact_cmp_surname);
        clock_gettime(CLOCK_MONOTONIC_RAW, &end);

        sum += nanoseconds(&beg, &end);
    }

    return sum / TIME_RUNS;
}
