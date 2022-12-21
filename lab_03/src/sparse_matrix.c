#include "sparse_matrix.h"

int sparsem_matrix_size_scan(size_t *col_n, size_t *row_m, FILE *stream)
{
    int temp[2];
    size_t sz = 2;
    int rc = input_ints(stream, temp, &sz, 2, " ");

    switch (rc)
    {
    case EXIT_INCORRECT_ELEMENT:
        rc = EXIT_INCORRECT_SPARSE_MATRIX_SIZE;
        break;
    case EXIT_DATA_OVERFLOW:
        rc = EXIT_SUCCESS;
        break;
    }

    if (sz != 2)
        rc = EXIT_INCORRECT_SPARSE_MATRIX_SIZE;

    if (rc)
        return rc;

    *col_n = temp[0];
    *row_m = temp[1];

    return EXIT_SUCCESS;
}

int sparsem_values_scan(sign_elems_t *vals, size_t *size, FILE *stream)
{
    *size = 0;
    int rc = input_ints(stream, vals->data + vals->size, size, ROWS_SIZE, " ");
    vals->size += *size;

    switch (rc)
    {
    case EXIT_INCORRECT_ELEMENT:
        rc = EXIT_INCORRECT_VALUE;
        break;
    case EXIT_DATA_OVERFLOW:
        rc = EXIT_TOO_MANY_VALUES;
        break;
    }

    return rc;
}

int sparsem_cols_inds_scan(cols_inds_t *inds, size_t *size, FILE *stream)
{
    *size = 0;
    int rc = input_ints(stream, inds->data + inds->size, size, ROWS_SIZE, " ");
    inds->size += *size;

    switch (rc)
    {
    case EXIT_INCORRECT_ELEMENT:
        rc = EXIT_INCORRECT_COLUMNS_INDEXES;
        break;
    case EXIT_DATA_OVERFLOW:
        rc = EXIT_TOO_MANY_COLUMNS_INDEXES;
        break;
    }

    return rc;
}

int sparsem_scan(sparse_matrix_t *matrix, FILE *stream)
{
    int rc = 0;
    
    printf("Введите полные размеры матрицы (Количество_Строк Количество_Столбцов): ");

    matrix->col_size = 0;
    matrix->row_size = 0;
    if ((rc = sparsem_matrix_size_scan(&(matrix->col_size), &(matrix->row_size), stream)))
        return rc;

    matrix->rows_rels.size = matrix->col_size;
    
    // Очищаем описания строк
    for (size_t i = 0; i < matrix->rows_rels.size; i++)
        matrix->rows_rels.rows[i].size = 0;

    printf("Введите номер строки: ");

    matrix->values.size = 0;
    size_t cur_row;
    while (!input_size(stream, &cur_row))
    {
        size_t temp_size = matrix->values.size;

        printf("Введите ненулевые элементы в строке (через пробел): ");

        // Считывание значений значащих чисел
        size_t inputed_vals_cnt = 0;
        if ((rc = sparsem_values_scan(&(matrix->values), &inputed_vals_cnt, stream)))
            return rc;
        if (inputed_vals_cnt > matrix->row_size)
            matrix->values.size -= (matrix->row_size - inputed_vals_cnt);

        printf("Введите номера столбцов этих элементов (через пробел): ");

        // Считывание позиций в строке значащих чисел
        size_t inputed_cols_inds_cnt = 0;
        if ((rc = sparsem_cols_inds_scan(&(matrix->cols_inds), &inputed_cols_inds_cnt, stream)))
            return rc;

        // Обработка различия по размеру ввода значений и позиций
        if (inputed_cols_inds_cnt < inputed_vals_cnt)
            return EXIT_TOO_FEW_COLUMNS_INDEXES;
        matrix->cols_inds.size = matrix->values.size;

        // Заполняем описание текущей строки
        for (size_t i = temp_size; i < matrix->values.size; i++)
        {
            row_relation_t *cur_rel = &(matrix->rows_rels.rows[cur_row]);
            cur_rel->size++;
            cur_rel->data[cur_rel->size - 1] = i;
        }

        printf("Введите номер строки: ");
    }

    return EXIT_SUCCESS;
}

void sparsem_print_matrix(sparse_matrix_t *matrix, int with_zeros, int formatted, FILE *stream)
{
    int spaces = PRINT_INT_WIDTH;
    //if (!formatted)
    spaces = 0;

    if (with_zeros)
    {
        for (size_t i = 0; i < matrix->rows_rels.size; i++)
        {
            row_relation_t *cur_rel = &(matrix->rows_rels.rows[i]);
            if (cur_rel->size == 0)
                for (size_t j = 0; j < matrix->row_size; j++)
                    fprintf(stream, "%-*d ", spaces, 0);
            else
            {
                size_t prev_col_ind = 0;
                for (size_t j = 0; j < cur_rel->size; i++)
                {
                    size_t cur_col_ind = matrix->cols_inds.data[cur_rel->data[i]];
                    int cur_value = matrix->values.data[cur_rel->data[i]];
                    for (size_t k = 0; k < cur_col_ind - prev_col_ind; k++)
                        fprintf(stream, "%-*d ", spaces, 0);

                    fprintf(stream, "%-*d ", spaces, cur_value);
                    prev_col_ind = cur_col_ind;
                }
            }
            fprintf(stream, "\n");
        }
    }
    else
    {
        if (!formatted)
        {
            for (size_t i = 0; i < matrix->values.size; i++)
                fprintf(stream, "%-*d ", spaces, matrix->values.data[i]);
            fprintf(stream, "\n");

            for (size_t i = 0; i < matrix->cols_inds.size; i++)
                fprintf(stream, "%-*d ", spaces, matrix->cols_inds.data[i]);
            fprintf(stream, "\n");

            for (size_t i = 0; i < matrix->rows_rels.size; i++)
                if (matrix->rows_rels.rows[i].size)
                {    
                    for (size_t j = 0; j < matrix->rows_rels.rows[i].size; j++)
                        fprintf(stream, "%-*d ", spaces, matrix->rows_rels.rows[i].data[j]);
                    fprintf(stream, "\n");
                }
        }
        else
        {
            fprintf(stream, "Массив ненулевых элементов: ");
            for (size_t i = 0; i < matrix->values.size; i++)
                fprintf(stream, "%-*d ", spaces, matrix->values.data[i]);
            fprintf(stream, "\n");

            fprintf(stream, "Номера столбцов ненулевых элементов: ");
            for (size_t i = 0; i < matrix->cols_inds.size; i++)
                fprintf(stream, "%-*d ", spaces, matrix->cols_inds.data[i]);
            fprintf(stream, "\n");

            fprintf(stream, "Связный список, содержащий описания строк\n");
            for (size_t i = 0; i < matrix->rows_rels.size; i++)
            {
                fprintf(stream, "Строка номер %zu: ", i);
                for (size_t j = 0; j < matrix->rows_rels.rows[i].size; j++)
                    fprintf(stream, "%-*d ", spaces, matrix->rows_rels.rows[i].data[j]);
                fprintf(stream, "\n");
            }
        }
    }
}

int sparsem_column_prod(sparse_matrix_t *matrix, vector_col_t *v_col, sparse_matrix_t *result)
{
    if (matrix->row_size != v_col->size)
        return EXIT_CANNOT_SPARSE_MATRIX_PRODUCT_COLUMN;

    result->col_size = matrix->rows_rels.size;
    result->row_size = 1;
    result->rows_rels.size = result->col_size;
    result->values.size = 0;
    for (size_t i = 0; i < result->rows_rels.size; i++)
        result->rows_rels.rows[i].size = 0;

    for (size_t i = 0; i < matrix->rows_rels.size; i++)
    {
        int sum = 0;
        for (size_t j = 0; j < matrix->rows_rels.rows[i].size; j++)
        {
            row_relation_t *cur_rel = &(matrix->rows_rels.rows[i]);
            int value = matrix->values.data[cur_rel->data[j]];
            size_t col_ind = matrix->cols_inds.data[cur_rel->data[j]];

            sum += value * v_col->data[col_ind];
        }

        if (sum)
        {
            if (!result->rows_rels.rows[i].size)
                result->rows_rels.rows[i].size++;

            result->values.size++;
            result->values.data[result->values.size - 1] = sum;

            result->cols_inds.size++;
            result->cols_inds.data[result->cols_inds.size - 1] = 0;

            result->rows_rels.rows[i].data[result->rows_rels.rows[i].size - 1] = result->values.size - 1;
        }
    }

    return EXIT_SUCCESS;
}

void sparsem_to_matrix(sparse_matrix_t *src, matrix_t *dst)
{
    dst->col_size = src->col_size;
    dst->row_size = src->row_size;

    for (size_t i = 0; i < dst->col_size; i++)
        for (size_t j = 0; j < dst->row_size; j++)
            dst->data[i][j] = 0;

    for (size_t i = 0; i < src->rows_rels.size; i++)
        for (size_t j = 0; j < src->rows_rels.rows[i].size; j++)
        {
            row_relation_t *cur_rel = &(src->rows_rels.rows[i]);
            int value = src->values.data[cur_rel->data[j]];
            size_t col_ind = src->cols_inds.data[cur_rel->data[j]];

            dst->data[i][col_ind] = value;
        }
}

void sparsem_from_matrix(sparse_matrix_t *dst, matrix_t *src)
{
    dst->col_size = src->col_size;
    dst->row_size = src->row_size;

    dst->values.size = 0;
    dst->cols_inds.size = 0;

    dst->rows_rels.size = src->col_size;

    for (size_t i = 0; i < dst->rows_rels.size; i++)
            dst->rows_rels.rows[i].size = 0;

    for (size_t i = 0; i < src->col_size; i++)
        for (size_t j = 0; j < src->row_size; j++)
            if (src->data[i][j])
            {
                dst->cols_inds.size++;
                dst->cols_inds.data[dst->cols_inds.size - 1] = j;

                dst->values.size++;
                dst->values.data[dst->values.size - 1] = src->data[i][j];

                dst->rows_rels.rows[i].size++;
                dst->rows_rels.rows[i].data[dst->rows_rels.rows[i].size - 1] = dst->values.size - 1;
            }
}

unsigned long long sparsem_col_prod_time(void *matrix, vector_col_t *v_col, void *result)
{
    unsigned long long sum = 0;   
    for (int i = 0; i < SPARSE_MATRIX_TIME_RUNS; i++)
    {
        struct timespec beg, end;

        clock_gettime(CLOCK_MONOTONIC_RAW, &beg);
        sparsem_column_prod((sparse_matrix_t *)matrix, v_col, (sparse_matrix_t *)result);
        clock_gettime(CLOCK_MONOTONIC_RAW, &end);

        sum += nanoseconds(&beg, &end);
    }

    return sum / SPARSE_MATRIX_TIME_RUNS;
}
