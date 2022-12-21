#ifndef __CONTACT_H__

#define __CONTACT_H__

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "date.h"
#include "phone_number.h"
#include "errors_contact.h"
#include "errors_input.h"

#define INPUT_LEN 255
#define POST_LEN 21
#define AGENCY_LEN 21
#define SURNAME_LEN 21
#define NAME_LEN 21
#define STREET_LEN 16
#define STATUS_LEN 21
#define PRINT_SURNAME_WIDTH 25
#define PRINT_NAME_WIDTH 25
#define PRINT_STREET_WIDTH 15
#define PRINT_HOUSE_WIDTH 10
#define PRINT_ADDRESS_WIDTH (PRINT_STREET_WIDTH + PRINT_HOUSE_WIDTH)
#define PRINT_STATUS_TYPE_WIDTH 25
#define PRINT_POST_WIDTH 25
#define PRINT_AGENCY_WIDTH 25
#define PRINT_STATUS_WIDTH 50
#define PRINT_INDEX_WIDTH 15
#define PRINT_CONTACT_WIDTH (PRINT_SURNAME_WIDTH + PRINT_NAME_WIDTH + PRINT_PHONE_WIDTH + PRINT_STATUS_TYPE_WIDTH + PRINT_STATUS_WIDTH + PRINT_ADDRESS_WIDTH + 7)


typedef struct
{
    char street[STREET_LEN];
    int house;
} address_t;

typedef struct
{
    date_t birthday;
} contact_private_t;

typedef struct
{
    char post[POST_LEN];
    char agency[AGENCY_LEN];
} contact_official_t;

typedef union
{
    contact_private_t private;
    contact_official_t official;
} contact_status_t;

typedef struct {
    char surname[SURNAME_LEN];
    char name[NAME_LEN];
    phone_number_t phone_number;
    address_t address;
    char status_type[STATUS_LEN];
    contact_status_t status;
} contact_t;

int contact_scan(contact_t *contact, FILE *stream);
void contact_fields_print(int formatted);
void contact_print(contact_t *contact, int formatted);
int contact_cmp_surname(const void *contact1, const void *contact2);
int contact_cmp_name(contact_t *contact1, contact_t *contact2);
int contact_cmp_phone_number(contact_t *contact1, contact_t *contact2);
int contact_cmp_official(contact_official_t *official1, contact_official_t *official2);
int contact_cmp_private(contact_private_t *private1, contact_private_t *private2);
int contact_cmp_status_type(char status_type1[STATUS_LEN], char status_type2[STATUS_LEN]);
int contact_cmp_status(contact_t *contact1, contact_t *contact2, int *rc);
int contact_predicate(contact_t *contact1, contact_private_t *private2);

#endif // __CONTACT_H__