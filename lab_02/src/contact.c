#include "../inc/contact.h"

int contact_scan(contact_t *contact, FILE *stream)
{
    char input[INPUT_LEN];
    if (fgets(input, INPUT_LEN, stream) == NULL)
        return EXIT_EMPTY_INPUT;
    
    size_t input_len = strlen(input);

    if (input[input_len - 1] != '\n')
        return EXIT_INPUT_OVERFLOW;
    input[input_len - 1] = '\0';
    input_len--;

    char *splitted_input = strtok(input, " \t");
    if (splitted_input == NULL || sscanf(splitted_input, "%s", contact->surname) != 1)
        return EXIT_INCORRECT_SURNAME;

    splitted_input = strtok(NULL, " \t");
    if (splitted_input == NULL || sscanf(splitted_input, "%s", contact->name) != 1)
        return EXIT_INCORRECT_NAME;

    splitted_input = strtok(NULL, " \t");
    int rc = EXIT_INCORRECT_PHONE;
    if (splitted_input == NULL || (rc = phone_sscan(splitted_input, &(contact->phone_number))))
        return rc;

    splitted_input = strtok(NULL, " \t");
    if (splitted_input == NULL || sscanf(splitted_input, "%s", contact->address.street) != 1)
        return EXIT_INCORRECT_STREET;

    splitted_input = strtok(NULL, " \t");
    if (splitted_input == NULL || sscanf(splitted_input, "%d", &(contact->address.house)) != 1)
        return EXIT_INCORRECT_HOUSE;

    splitted_input = strtok(NULL, " \t");
    contact->status_type[0] = '\0';
    if (splitted_input == NULL)
        return EXIT_INCORRECT_STATUS;
    strcpy(contact->status_type, splitted_input);

    splitted_input = strtok(NULL, " ");
    if (!strcmp(contact->status_type, "private"))
    {
        rc = EXIT_INCORRECT_DATE;
        if (splitted_input == NULL || (rc = date_sscan(splitted_input, &(contact->status.private.birthday))))
            return rc;
    }
    else if (!strcmp(contact->status_type, "official"))
    {
        if (splitted_input == NULL || sscanf(splitted_input, "%s", contact->status.official.post) != 1)
            return EXIT_INCORRECT_POST;

        splitted_input = strtok(NULL, " \t");
        if (splitted_input == NULL || sscanf(splitted_input, "%s", contact->status.official.agency) != 1)
            return EXIT_INCORRECT_AGENCY;
    }
    else 
        return EXIT_INCORRECT_STATUS;

    return EXIT_SUCCESS;
}

void contact_fields_print(int formatted)
{
    if (formatted)
    {
        for (size_t j = 0; j < PRINT_CONTACT_WIDTH; j++)
            printf("_");
        printf("\n");
        printf("|%*s|", PRINT_SURNAME_WIDTH, "Surname");
        printf("%*s|", PRINT_NAME_WIDTH, "Name");
        printf("%*s|", PRINT_PHONE_WIDTH, "Phone number");
        printf("%*s|", PRINT_ADDRESS_WIDTH, "Address");
        printf("%*s|", PRINT_STATUS_TYPE_WIDTH, "Status");
        printf("%*s|\n", PRINT_STATUS_WIDTH, "Birthday \\ Post Agency");
        for (size_t j = 0; j < PRINT_CONTACT_WIDTH; j++)
                printf("_");
        printf("\n");
    }
    else 
    {
        printf("%s ", "Surname");
        printf("%s ", "Name");
        printf("%s ", "Phone number");
        printf("%s ", "Address");
        printf("%s ", "Status");
        printf("%s", "Birthday \\ Post Agency\n");
    }
}

void contact_print(contact_t *contact, int formatted)
{
    if (formatted)
    {
        printf("|%-*s|", PRINT_SURNAME_WIDTH, contact->surname);
        printf("%-*s|", PRINT_NAME_WIDTH, contact->name);
        phone_print(&(contact->phone_number), 1);
        printf("%-*s%-*d|", PRINT_STREET_WIDTH, contact->address.street, PRINT_HOUSE_WIDTH, contact->address.house);
        printf("%-*s|", PRINT_STATUS_TYPE_WIDTH, contact->status_type);
        if (!strcmp(contact->status_type, "private"))
            date_print(&(contact->status.private.birthday), 1);
        else if (!strcmp(contact->status_type, "official"))
            printf("%-*s%-*s|", PRINT_POST_WIDTH, contact->status.official.post, PRINT_AGENCY_WIDTH, contact->status.official.agency);
    }
    else
    {
        printf("%s ", contact->surname);
        printf("%s ", contact->name);
        phone_print(&(contact->phone_number), 0);
        printf(" %s %d", contact->address.street, contact->address.house);
        printf(" %s ", contact->status_type);
        if (!strcmp(contact->status_type, "private"))
            date_print(&(contact->status.private.birthday), 0);
        else if (!strcmp(contact->status_type, "official"))
            printf("%s %s", contact->status.official.post, contact->status.official.agency);
    }

    printf("\n");
}

int contact_cmp_surname(const void *contact1, const void *contact2)
{
    return strcmp(((const contact_t *)contact1)->surname, ((const contact_t *)contact2)->surname);
}

int contact_cmp_name(contact_t *contact1, contact_t *contact2)
{
    return strcmp(contact1->name, contact2->name);
}

int contact_cmp_phone_number(contact_t *contact1, contact_t *contact2)
{
    return phone_cmp(&(contact1->phone_number), &(contact2->phone_number));
}

int contact_cmp_official(contact_official_t *official1, contact_official_t *official2)
{
    int cmp_post = strcmp(official1->post, official2->post);
    int cmp_agency = strcmp(official1->agency, official2->agency);

    if (cmp_post)
        return cmp_post;
    
    return cmp_agency;
}

int contact_cmp_private(contact_private_t *private1, contact_private_t *private2)
{
    return date_diff_days(&(private1->birthday), &(private2->birthday));
}

int contact_cmp_status_type(char status_type1[STATUS_LEN], char status_type2[STATUS_LEN])
{
    return strcmp(status_type1, status_type2);
}

int contact_cmp_status(contact_t *contact1, contact_t *contact2, int *rc)
{
    *rc = 0;
    if (contact_cmp_status_type(contact1->status_type, contact2->status_type))
    {
        *rc = EXIT_STATUS_TYPE_DIFFERS;
        return *rc;
    }
    
    if (!strcmp(contact1->status_type, "official"))
        return contact_cmp_official(&(contact1->status.official), &(contact2->status.official));
    
    return contact_cmp_private(&(contact1->status.private), &(contact2->status.private));
}

int contact_predicate(contact_t *contact1, contact_private_t *private2)
{
    if (contact_cmp_status_type(contact1->status_type, "private") != 0)
        return 0;
    int cmpy = date_diff_years(&(contact1->status.private.birthday), &(private2->birthday));
    int cmp = contact_cmp_private(&(contact1->status.private), private2);
    return cmpy <= 0 && cmp >= 0 && cmp <= 7;
}