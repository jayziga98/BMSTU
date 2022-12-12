#ifndef __CONTACTS_H__

#define __CONTACTS_H__

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "contact.h"
#include "errors_contacts.h"
#include "my_time.h"

#define CONTACTS_SIZE 50
#define TIME_RUNS 1000

typedef struct
{
    int source_index;
    char surname[SURNAME_LEN];
} key_t;

typedef struct
{
    size_t size;
    key_t data[CONTACTS_SIZE];
} keys_t;

typedef struct
{
    size_t size;
    contact_t data[CONTACTS_SIZE];
} contacts_t;

int contacts_scan(contacts_t *contacts, size_t n, keys_t *keys, FILE *stream);
void contacts_print(contacts_t *contacts, int formatted);
int contacts_add(contacts_t *contacts, contact_t *contact, keys_t *keys);
int keys_init(keys_t *keys, contacts_t *contacts);
int keys_add(keys_t *keys, contact_t *contact);
void swap(void *ptr1, void *ptr2, size_t size);
void contacts_del_by_pos(contacts_t *contacts, size_t pos);
int contacts_del_by_key(contacts_t *contacts, char key[SURNAME_LEN], keys_t *keys, int *n);
int contacts_print_by(contacts_t *contacts, contact_private_t *date, int (*predicate)(contact_t *, contact_private_t *));
void contacts_print_from_keys(contacts_t *contacts, keys_t *keys, int formatted);
void contacts_from_keys(contacts_t *contacts, keys_t *keys, contacts_t *result);
void keys_fields_print(int formatted);
void keys_print(keys_t *keys, int formatted);
int key_cmp(const void *key1, const void *key2);
void *find_min(void *ptr_beg, void *ptr_end, size_t size, int (*comp)(const void *, const void *));
void mysort(void *base, size_t nmemb, size_t size, int (*compar)(const void *, const void *));
unsigned long long time_sort_from_keys(contacts_t *contacts, keys_t *keys, void (*sort)(void *, size_t, size_t, int (*)(const void *, const void *)));
unsigned long long time_sort_contacts(contacts_t *contacts, void (*sort)(void *, size_t, size_t, int (*)(const void *, const void *)));

#endif // #ifndef __CONTACTS_H__
