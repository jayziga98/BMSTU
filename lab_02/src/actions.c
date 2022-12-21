#include "../inc/actions.h"

int handle_action(int com, contacts_t *contacts, keys_t *keys)
{
    int rc = 0;

    switch (com)
    {
        case 0:
            break;
        case 1:
            rc = exec_command1(contacts, keys);
            break;
        case 2:
            rc = exec_command2(contacts, keys);
            break;
        case 3:
            exec_command3(contacts);
            break;
        case 4:
            exec_command4(contacts);
            break;
        case 5:
            rc = exec_command5(contacts, keys);
            break;
        case 6:
            rc = exec_command6(contacts, keys);
            break;
        case 7:
            rc = exec_command7(contacts);
            break;
        case 8:
            exec_command8(keys);
            break;
        case 9:
            exec_command9(keys);
            break;
        case 10:
            exec_command10(keys);
            break;
        case 11:
            exec_command11(keys);
            break;
        case 12:
            exec_command12(contacts);
            break;
        case 13:
            exec_command13(contacts);
            break;
        case 14:
            exec_command14(contacts, keys);
            break;
        case 15:
            exec_command15(contacts, keys);
            break;
        case 16:
            exec_command16(contacts, keys);
            break;
        case 17:
            exec_command17(contacts, keys);
            break;
        case 18:
            exec_command18();
            break;
        default:
            printf("Неверная команда!\n");
    }

    return rc;
}

void print_abonent_help()
{
    printf("\t ? Через пробел вводится: |Фамилия Имя Номер_Телефона Адресс Статус Доп._Информация|\n");
    printf("\t ? Фамилия(20 символов)\n");
    printf("\t ? Имя(20 символов)\n");
    printf("\t ? Номер_телефона(необязательный знак плюс, 11 цифр) - [+]КОД_СТРАНЫ(1 цифра)[-]КОД_РЕГИОНА(3 цифры)[-]НОМЕР(7 цифр)\n");
    printf("\t ? Адрес - Улица(15 символов) Номер_дома\n");
    printf("\t ? Статус(20 символов) - |Личный - private / Служебный - official|\n");
    printf("\t ? Доп._информация - |Личный - день рождения ДЕНЬ.МЕСЯЦ.ГОД / Служебный - Должность(20 символов) Организация(20 символов)| \n");
    printf("\n");
}

void print_menu_sep()
{
    for (int i = 0; i < 89; i++)
        printf("~");
    printf("\n");
}

void print_menu()
{
    printf("\n~ Действия:\t\t\t\t\t\t\t\t\t\t~\n");
    print_menu_sep();
    printf("~  0 - Завершить.\t\t\t\t\t\t\t\t\t~\n");

    print_menu_sep();
    printf("~  1 - Ввести список абонентов.\t\t\t\t\t\t\t\t~\n");
    printf("~  2 - Ввести список абонентов. <ФАЙЛОВЫЙ ввод>\t\t\t\t\t\t~\n");

    print_menu_sep();
    printf("~  3 - Вывести список абонентов. <ФОРМАТИРОВАННЫЙ вывод>\t\t\t\t~\n");
    printf("~  4 - Вывести список абонентов.\t\t\t\t\t\t\t~\n");

    print_menu_sep();
    printf("~  5 - Добавить абонента в конец списка.\t\t\t\t\t\t~\n");
    printf("~  6 - Удалить абонентов по фамилии.\t\t\t\t\t\t\t~\n");
    printf("~  7 - Найти всех абонентов, у которых день рождения в ближайшую неделю.\t\t~\n");

    print_menu_sep();
    printf("~  8 - Вывести таблицу ключей. <ФОРМАТИРОВАННЫЙ вывод>\t\t\t\t\t~\n");
    printf("~  9 - Вывести таблицу ключей.\t\t\t\t\t\t\t\t~\n");

    print_menu_sep();
    printf("~ 10 - Упорядочить и вывести таблицу ключей. <ФОРМАТИРОВАННЫЙ вывод>\t\t\t~\n");
    printf("~ 11 - Упорядочить и вывести таблицу ключей.\t\t\t\t\t\t~\n");

    print_menu_sep();
    printf("~ 12 - Упорядочить и вывести исходную таблицу. <ФОРМАТИРОВАННЫЙ вывод>\t\t\t~\n");
    printf("~ 13 - Упорядочить и вывести исходную таблицу.\t\t\t\t\t\t~\n");

    print_menu_sep();
    printf("~ 14 - Упорядочить таблицу ключей и вывести по ней исходную. <ФОРМАТИРОВАННЫЙ вывод>\t~\n");
    printf("~ 15 - Упорядочить таблицу ключей и вывести по ней исходную.\t\t\t\t~\n");

    print_menu_sep();
    printf("~ 16 - Сравнить эффективность пунктов 12-13 и 14-15.\t\t\t\t\t~\n");
    printf("~ 17 - Сравнить эффективность при использовании различных сортировках.\t\t\t~\n");
    printf("~ 18 - Сравнить объем используемой памяти.\t\t\t\t\t\t~\n");

    print_menu_sep();
}

int exec_command1(contacts_t *contacts, keys_t *keys)
{
    size_t n;

    printf("Введите количество абонентов (от 0 до 40)\n");
    printf("Если ввести 0 - таблица очистится! : ");
    scanf("%zu", &n);
    fflush(stdin);

    print_abonent_help();
    int rc;
    if((rc = contacts_scan(contacts, n, keys, stdin)))
        return rc;

    if (contacts->size)
        printf("\n\t ! Абоненты успешно записаны\n");
    else
        printf("\n\t ! Список абонентов пуст!\n");

    return EXIT_SUCCESS;
}

int exec_command2(contacts_t *contacts, keys_t *keys)
{
    size_t n = 0;

    printf("Введите название файла(40 символов): ");
    char filename[FILENAME_LEN];
    if (scanf("%40s", filename) != 1)
        return EXIT_INCORRECT_FILENAME;
    fflush(stdin);

    FILE *f = fopen(filename, "r");

    int rc = 0;
    if (f != NULL)
    {
        rc = contacts_scan(contacts, n, keys, f);
        fclose(f);
    }
    else
        rc = EXIT_INCORRECT_FILENAME;
    
    if(!rc)
    {
        if (contacts->size)
            printf("\n\t ! Абоненты успешно записаны\n");
        else
            printf("\n\t ! Список абонентов пуст!\n");
    }

    return rc;
}

void exec_command3(contacts_t *contacts)
{
    contact_fields_print(1);

    contacts_print(contacts, 1);
}

void exec_command4(contacts_t *contacts)
{
    contact_fields_print(0);

    contacts_print(contacts, 0);
}

int exec_command5(contacts_t *contacts, keys_t *keys)
{
    int rc = 0;

    print_abonent_help();
    printf("Введите абонента: ");
    contact_t contact;
    if ((rc = contact_scan(&contact, stdin)))
        return rc;

    if ((rc = contacts_add(contacts, &contact, keys)))
        return rc;
    
    printf("\n\t ! Абонент успешно добавлен\n");

    return EXIT_SUCCESS;
}

int exec_command6(contacts_t *contacts, keys_t *keys)
{
    char key[SURNAME_LEN];
    printf("Введите фамилию(20 символов): ");
    if (scanf("%20s", key) != 1)
        return EXIT_INCORRECT_SURNAME;
    fflush(stdin);

    int n = 0;
    int rc = 0;
    if ((rc = contacts_del_by_key(contacts, key, keys, &n)))
        return rc;

    if (n)
        printf("\n\t ! Абоненты успешно удалены\n");
    else
        printf("\n\t ! Абонентов с такой фамилией - нет\n");

    return EXIT_SUCCESS;
}

int exec_command7(contacts_t *contacts)
{
    int rc = 0;

    char input[DATE_LEN];
    contact_private_t private;
    printf("Введите текущую дату в формате ДЕНЬ.МЕСЯЦ.ГОД: ");
    if (scanf("%20s", input) != 1)
        return EXIT_INCORRECT_DATE;
    fflush(stdin);
    if ((rc = date_sscan(input, &(private.birthday))))
        return rc;

    if (contacts_print_by(contacts, &private, contact_predicate))
        printf("\n\t ! Не забудьте поздравить их с днём рождения\n");
    else
        printf("\n\t ! В ближайшую неделю нет дней рождения\n");

    return EXIT_SUCCESS;
}

void exec_command8(keys_t *keys)
{
    keys_fields_print(1);

    keys_print(keys, 1);
}

void exec_command9(keys_t *keys)
{
    keys_fields_print(0);

    keys_print(keys, 0);
}

void exec_command10(keys_t *keys)
{
    if (keys->size)
    {
        mysort(keys->data, keys->size, sizeof(keys->data[0]), key_cmp);
        exec_command8(keys);
    }
    else
        printf("\t ! Таблица ключей пуста\n");
}

void exec_command11(keys_t *keys)
{
    if (keys->size)
    {
        mysort(keys->data, keys->size, sizeof(keys->data[0]), key_cmp);
        exec_command9(keys);
    }
    else
        printf("\t ! Таблица ключей пуста\n");
}

void exec_command12(contacts_t *contacts)
{
    if (contacts->size)
    {
        mysort(contacts->data, contacts->size, sizeof(contacts->data[0]), contact_cmp_surname);
        exec_command3(contacts);
    }
    else
        printf("\t ! Абонентская книжка пуста\n");
}

void exec_command13(contacts_t *contacts)
{
    if (contacts->size)
    {
        mysort(contacts->data, contacts->size, sizeof(contacts->data[0]), contact_cmp_surname);
        exec_command4(contacts);
    }
    else
        printf("\t ! Абонентская книжка пуста\n");
}

void exec_command14(contacts_t *contacts, keys_t *keys)
{
    if (!keys->size)
        printf("\t ! Таблица ключей пуста\n");
    else
    {
        mysort(keys->data, keys->size, sizeof(keys->data[0]), key_cmp);
        contact_fields_print(1);
        contacts_print_from_keys(contacts, keys, 1);
    }
}

void exec_command15(contacts_t *contacts, keys_t *keys)
{
    if (!keys->size)
        printf("\t ! Таблица ключей пуста\n");
    else
    {
        mysort(keys->data, keys->size, sizeof(keys->data[0]), key_cmp);
        contacts_print_from_keys(contacts, keys, 0);
    }
}

void print_time_sep(int n)
{
    for (int i = 0; i < n; i++)
        printf("_");
    printf("\n");
}

void exec_command16(contacts_t *contacts, keys_t *keys)
{
    unsigned long long t = time_sort_contacts(contacts, mysort);
    unsigned long long t_wkeys = time_sort_from_keys(contacts, keys, mysort);

    
    print_time_sep(PRINT_TIME_WIDTH + 3);
    printf("|%*s", PRINT_TIME_WIDTH / 2,  "Sort conctacts, ns");
    printf("|%*s|\n", PRINT_TIME_WIDTH / 2,  "Sort keys and get sorted contacts, ns");
    print_time_sep(PRINT_TIME_WIDTH + 3);

    printf("|%-*llu", PRINT_TIME_WIDTH / 2, t);
    printf("|%-*llu|\n", PRINT_TIME_WIDTH / 2, t_wkeys);
    print_time_sep(PRINT_TIME_WIDTH + 3);

}

void exec_command17(contacts_t *contacts, keys_t *keys)
{
    unsigned long long t = time_sort_contacts(contacts, mysort);
    unsigned long long t_wkeys = time_sort_from_keys(contacts, keys, mysort);

    unsigned long long qt = time_sort_contacts(contacts, qsort);
    unsigned long long qt_wkeys = time_sort_from_keys(contacts, keys, qsort);

    
    print_time_sep((PRINT_TIME_WIDTH * 3) / 2 + 4);
    printf("|%*s", PRINT_TIME_WIDTH / 2,  " ");
    printf("|%*s", PRINT_TIME_WIDTH / 2,  "Sort conctacts, ns");
    printf("|%*s|\n", PRINT_TIME_WIDTH / 2,  "Sort keys and get sorted contacts, ns");
    print_time_sep((PRINT_TIME_WIDTH * 3) / 2 + 4);

    printf("|%-*s", PRINT_TIME_WIDTH / 2, "Selection sort");

    printf("|%-*llu", PRINT_TIME_WIDTH / 2, t);
    printf("|%-*llu|\n", PRINT_TIME_WIDTH / 2, t_wkeys);
    print_time_sep((PRINT_TIME_WIDTH * 3) / 2 + 4);

    printf("|%-*s", PRINT_TIME_WIDTH / 2, "Quick sort");

    printf("|%-*llu", PRINT_TIME_WIDTH / 2, qt);
    printf("|%-*llu|\n", PRINT_TIME_WIDTH / 2, qt_wkeys);
    print_time_sep((PRINT_TIME_WIDTH * 3) / 2 + 4);
}

void exec_command18()
{
    size_t m = sizeof(contact_t);
    size_t m_wkeys = m + sizeof(key_t);

    print_time_sep(PRINT_MEM_WIDTH + 3);
    printf("|%*s", PRINT_MEM_WIDTH / 2,  "Contact, bytes");
    printf("|%*s|\n", PRINT_MEM_WIDTH / 2,  "Contact with key, bytes");
    print_time_sep(PRINT_MEM_WIDTH + 3);

    printf("|%-*zu", PRINT_MEM_WIDTH / 2, m);
    printf("|%-*zu|\n", PRINT_MEM_WIDTH / 2, m_wkeys);
    print_time_sep(PRINT_MEM_WIDTH + 3);
}
