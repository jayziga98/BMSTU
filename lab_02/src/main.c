#include <stdio.h>
#include <stdlib.h>

#include "../inc/contacts.h"
#include "../inc/actions.h"

int error_handler(int rc);

int main()
{
    printf("Программа позволяет работать со списком абонентов с помощью предложенного меню\n");

    contacts_t contacts;
    contacts.size = 0;
    keys_t keys;
    keys.size = 0;
    for (int com = -1, com_cnt = 0; com != 0; com_cnt++, com_cnt %= 3)
    {
        fflush(stdin);
        if (!com_cnt)
            print_menu();

        int rc = 0;

        printf("\n > Выполнить команду №: ");
        if (scanf("%d", &com) == 1)
        {
            printf("\n");
            fflush(stdin);

            rc = handle_action(com, &contacts, &keys);

            if (rc)
                return error_handler(rc);
        }
        else
            printf("Введите цифру от 0 до 18!");
    }

    return EXIT_SUCCESS;
}

int error_handler(int rc)
{
    switch (rc)
    {
        case EXIT_INCORRECT_FILENAME:
            printf("Ошибка: Вы ввели некорректное имя файла!");
            break;
        case EXIT_EMPTY_INPUT:
            printf("Ошибка: Вы ничего не ввели!");
            break;
        case EXIT_INPUT_OVERFLOW:
            printf("Ошибка: Вы ввели слишком длинную строку!");
            break;
        case EXIT_INCORRECT_DATE:
            printf("Ошибка: Вы ввели некорректную дату!");
            break;
        case EXIT_DAY_INCORRECT_SYMBOLS:
            printf("Ошибка: Вы ввели некорректные символы при указании дня!");
            break;
        case EXIT_MONTH_INCORRECT_SYMBOLS:
            printf("Ошибка: Вы ввели некорректные символы при указании месяца!");
            break;
        case EXIT_YEAR_INCORRECT_SYMBOLS:
            printf("Ошибка: Вы ввели некорректные символы при указании года!");
            break;
        case EXIT_INCORRECT_PHONE:
            printf("Ошибка: Вы ввели некорректный номер телефона!");
            break;
        case EXIT_INCORRECT_STREET:
            printf("Ошибка: Вы ввели некорректную улицу!");
            break;
        case EXIT_INCORRECT_HOUSE:
            printf("Ошибка: Вы ввели некорректный номер дома!");
            break;
        case EXIT_STATUS_TYPE_DIFFERS:
            printf("Ошибка: Статус телефонов отличается!");
            break;
        case EXIT_INCORRECT_SURNAME:
            printf("Ошибка: Вы ввели некорректную фамилию!");
            break;
        case EXIT_INCORRECT_NAME:
            printf("Ошибка: Вы ввели некорректное имя!");
            break;
        case EXIT_INCORRECT_STATUS:
            printf("Ошибка: Вы ввели некорректный статус!");
            break;
        case EXIT_INCORRECT_POST:
            printf("Ошибка: Вы ввели некорректную должность!");
            break;
        case EXIT_INCORRECT_AGENCY:
            printf("Ошибка: Вы ввели некорректную организацию!");
            break;
        case EXIT_CONTACTS_OVERFLOW:
            printf("Ошибка: слишком много контактов (> 50)!");
            break;
        case EXIT_KEYS_OVERFLOW:
            printf("Ошибка: слишком много ключей (> 50)!");
            break;
        default:
            printf("Ошибка: Неизвестная ошибка!");
    }

    return rc;
}
