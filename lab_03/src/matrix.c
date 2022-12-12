#include "matrix.h"

int matrix_size_scan(size_t *col_n, size_t *row_m, FILE *stream)
{
    int temp[2];
    size_t sz = 2;
    int rc = input_ints(stream, temp, &sz, 2, " ");

    switch (rc)
    {
    case EXIT_INCORRECT_ELEMENT:
        rc = EXIT_INCORRECT_MATRIX_SIZE;
        break;
    case EXIT_DATA_OVERFLOW:
        rc = EXIT_SUCCESS;
        break;
    }

    if (sz != 2)
        rc = EXIT_INCORRECT_MATRIX_SIZE;

    if (rc)
        return rc;

    *col_n = temp[0];
    *row_m = temp[1];

    return EXIT_SUCCESS;
}

int matrix_scan(matrix_t *matrix, FILE *stream)
{
    int rc = 0;
    
    matrix->col_size = 0;
    matrix->row_size = 0;

    if (stream == stdin)
    {
        printf("Введите размеры матрицы (Количество_Строк Количество_Столбцов): ");
        if ((rc = matrix_size_scan(&(matrix->col_size), &(matrix->row_size), stream)))
            return rc;

        for (size_t i = 0; i < matrix->col_size; i++)
        {
            printf("Введите элементы строки (через пробел): ");
            size_t cnt;
            if ((rc = input_ints(stream, matrix->data[i], &cnt, ROWS_SIZE, " ")))
                return rc;

            if (cnt != matrix->row_size)
                return EXIT_INCORRECT_AMOUNT_ROW_ELEMENTS_INPUTTED;
        }
    }
    else
    {
        for (; !rc; matrix->col_size++)
        {
            size_t cnt;

            if ((rc = input_ints(stream, matrix->data[matrix->col_size], &cnt, ROWS_SIZE, " ")))
                break;

            if (!matrix->row_size)
                matrix->row_size = cnt;

            if (cnt != matrix->row_size)
                rc = EXIT_INCORRECT_AMOUNT_ROW_ELEMENTS_INPUTTED;
        }
    }

    return EXIT_SUCCESS;
}

void matrix_print(matrix_t *matrix, int formatted, FILE *stream)
{
    int spaces = PRINT_INT_WIDTH;
    if (!formatted)
        spaces = 0;

    for (size_t i = 0; i < matrix->col_size; i++, fprintf(stream, "\n"))
        for (size_t j = 0; j < matrix->row_size; j++)
            fprintf(stream, "%-*d ", spaces, matrix->data[i][j]);
}

int matrix_column_prod(matrix_t *matrix, vector_col_t *v_col, vector_col_t *result)
{
    if (matrix->row_size != v_col->size)
        return EXIT_CANNOT_MATRIX_PRODUCT_COLUMN;

    result->size = matrix->row_size;
    for (size_t i = 0; i < result->size; i++)
        result->data[i] = 0;

    for (size_t i = 0; i < matrix->col_size; i++)
        for(size_t j = 0; j < matrix->row_size; j++)
            result->data[i] += matrix->data[i][j] * v_col->data[j]; 

    return EXIT_SUCCESS;
}

void matrix_from_column(matrix_t *dst, vector_col_t *src)
{
    dst->row_size = 1;
    dst->col_size = src->size;
    for (size_t i = 0; i < src->size; i++)
        dst->data[i][dst->row_size - 1] = src->data[i];
}

// sparsity = (100 * zero_count) / (matrix_n * matrix_m) - percent of zero amount in matrix
// zero_count = (matrix_n * matrix_m * sparsity) / 100
// sparsity > 100 == 100
// sparsity < 0 == 0
void matrix_generate(matrix_t *matrix, int sparsity)
{
    if (sparsity > 100)
        sparsity = 100;
    if (sparsity < 0)
        sparsity = 0;
    
    int zero_am = 0;
    if (sparsity)
        zero_am = (matrix->row_size * matrix->col_size * sparsity) / 100;

    int num_period = 111;
    int num = 0;

    int used[COLS_SIZE][ROWS_SIZE];
    for (size_t i = 0; i < COLS_SIZE; i++)
        for (size_t j = 0; j < ROWS_SIZE; j++)
            used[i][j] = 0;
    while (zero_am)
    {
        zero_am--;
        size_t i = (rand() % (matrix->col_size));
        size_t j = (rand() % (matrix->row_size));
        while (used[i][j])
        {
            i = (rand() % (matrix->col_size));
            j = (rand() % (matrix->row_size));
        }
        matrix->data[i][j] = 0;
        used[i][j] = 1;
    }
    for (size_t i = 0; i < matrix->col_size; i++)
        for (size_t j = 0; j < matrix->row_size; j++)
            if (!used[i][j]){
                num++;
                matrix->data[i][j] = num % num_period + 1;
            }

    // for (size_t i = 0; i < matrix->col_size; i++)
    //     for (size_t j = 0; j < matrix->row_size; j++)
    //         if (zero_am)
    //         {
    //             matrix->data[i][j] = 0;
    //             zero_am--;
    //         }
    //         else
    //         {
    //             num++;
    //             matrix->data[i][j] = num % num_period + 1;
    //         }
}

unsigned long long matrix_col_prod_time(void *matrix, vector_col_t *v_col, void *result)
{
    unsigned long long sum = 0;   
    for (int i = 0; i < MATRIX_TIME_RUNS; i++)
    {
        struct timespec beg, end;

        clock_gettime(CLOCK_MONOTONIC_RAW, &beg);
        matrix_column_prod((matrix_t *)matrix, v_col, (vector_col_t *)result);
        clock_gettime(CLOCK_MONOTONIC_RAW, &end);

        sum += nanoseconds(&beg, &end);
    }

    return sum / MATRIX_TIME_RUNS;
}
