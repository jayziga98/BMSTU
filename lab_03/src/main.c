#include <stdio.h>
#include <stdlib.h>

#include "sparse_matrix.h"
#include "input.h"
#include "actions.h"

int error_handler(int rc);

int main()
{
    printf("Программа позволяет выполнять обработку матриц с помощью предложенного меню \n");

    sparse_matrix_t sprs;
    matrix_t m;
    for (int com = -1, com_cnt = 0; com != 0; com_cnt++, com_cnt %= 3)
    {
        if (!com_cnt)
            actions_print();

        int rc = 0;

        printf("\n > Выполнить команду №: ");
        if (!input_int(stdin, &com))
        {
            printf("\n");

            rc = actions_handler(com, &sprs, &m);

            if (rc)
                return error_handler(rc);
        }
        else
        {
            printf("%d\n", com);
            printf("\t! Введите цифру от 0 до 10!\n");
        }
    }

    return EXIT_SUCCESS;
}

int error_handler(int rc)
{
    switch (rc)
    {
        case EXIT_INCORRECT_INPUT:
            printf("Ошибка: Некорректный ввод!");
            break;
        case EXIT_INPUT_OVERFLOW:
            printf("Ошибка: Слишком длинный ввод!");
            break;
        case EXIT_INCORRECT_ELEMENT:
            printf("Ошибка: Вы ввели некорректный элемент!");
            break;
        case EXIT_DATA_OVERFLOW:
            printf("Ошибка: Переполнение при попытке записать ввод!");
            break;
        case EXIT_CANNOT_MATRIX_PRODUCT_COLUMN:
            printf("Ошибка: Невозможно умножить матрицу на столбец (Размер столбца должен совпадать с размером строки матрицы)!");
            break;
        case EXIT_INCORRECT_VALUE:
            printf("Ошибка: Вы ввели неверное число!");
            break;
        case EXIT_TOO_MANY_VALUES:
            printf("Ошибка: Вы ввели слишком много чисел!");
            break;
        case EXIT_INCORRECT_SPARSE_MATRIX_SIZE:
            printf("Ошибка: Вы ввели некорректный размер разреженной матрицы!");
            break;
        case EXIT_INCORRECT_MATRIX_SIZE:
            printf("Ошибка: Вы ввели некорректный размер матрицы!");
            break;
        case EXIT_INCORRECT_COLUMNS_INDEXES:
            printf("Ошибка: ВЫ ввели некорректный номера столбцов для чисел!");
            break;
        case EXIT_TOO_MANY_COLUMNS_INDEXES:
            printf("Ошибка: Вы ввели слишком много номеров столбцов!");
            break;
        case EXIT_TOO_FEW_COLUMNS_INDEXES:
            printf("Ошибка: Вы ввели слишком мало номеров столбцов!");
            break;
        case EXIT_CANNOT_SPARSE_MATRIX_PRODUCT_COLUMN:
            printf("Ошибка: Невозможно умножить матрицу на столбец (Размер столбца должен совпадать с размером строки матрицы)!");
            break;
        case EXIT_INCORRECT_FILENAME:
            printf("Ошибка: Некорректное имя файла!");
            break;
        case EXIT_INCORRECT_AMOUNT_ROW_ELEMENTS_INPUTTED:
            printf("Ошибка: Введено некорректное число элементов в строке!");
            break;
        default:
            printf("Ошибка: Неизвестная ошибка!");
    }

    return rc;
}