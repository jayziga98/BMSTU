#include "actions.h"

void actions_print()
{
    int com = 0;

    printf("\n");

    // 0
    printf("~ %*d - %-*s\n", ACTIONS_NUM_PRINT_WIDTH, com, ACTIONS_PRINT_WIDTH, "Завершить."), com++;

    printf("\n");
    
    // 1
    printf("~ %*d - %-*s\n", ACTIONS_NUM_PRINT_WIDTH, com, ACTIONS_PRINT_WIDTH, "Ввести разреженную матрицу."), com++;
    // 2
    printf("~ %*d - %-*s\n", ACTIONS_NUM_PRINT_WIDTH, com, ACTIONS_PRINT_WIDTH, "Ввести разреженную матрицу. <ФАЙЛОВЫЙ ВВОД>"), com++;

    printf("\n");

    // 3
    printf("~ %*d - %-*s\n", ACTIONS_NUM_PRINT_WIDTH, com, ACTIONS_PRINT_WIDTH, "Ввести матрицу."), com++;
    // 4
    printf("~ %*d - %-*s\n", ACTIONS_NUM_PRINT_WIDTH, com, ACTIONS_PRINT_WIDTH, "Ввести матрицу. <ФАЙЛОВЫЙ ВВОД>"), com++;

    printf("\n");

    // 5
    printf("~ %*d - %-*s\n", ACTIONS_NUM_PRINT_WIDTH, com, ACTIONS_PRINT_WIDTH, "Напечатать матрицу."), com++;
    // 6
    printf("~ %*d - %-*s\n", ACTIONS_NUM_PRINT_WIDTH, com, ACTIONS_PRINT_WIDTH, "Напечатать матрицу. <ФОРМАТИРОВАННЫЙ ВЫВОД>"), com++;
    // 7
    printf("~ %*d - %-*s\n", ACTIONS_NUM_PRINT_WIDTH, com, ACTIONS_PRINT_WIDTH, "Напечатать разреженную матрицу."), com++;
    // 8
    printf("~ %*d - %-*s\n", ACTIONS_NUM_PRINT_WIDTH, com, ACTIONS_PRINT_WIDTH, "Напечатать разреженную матрицу. <ФОРМАТИРОВАННЫЙ ВЫВОД>"), com++;

    printf("\n");

    // 9
    printf("~ %*d - %-*s\n", ACTIONS_NUM_PRINT_WIDTH, com, ACTIONS_PRINT_WIDTH, "Напечатать матрицу. <ФАЙЛОВЫЙ ВЫВОД>"), com++;
    // 10
    printf("~ %*d - %-*s\n", ACTIONS_NUM_PRINT_WIDTH, com, ACTIONS_PRINT_WIDTH, "Напечатать матрицу. <ФОРМАТИРОВАННЫЙ ВЫВОД> <ФАЙЛОВЫЙ ВЫВОД>"), com++;

    printf("\n");

    // 11
    printf("~ %*d - %-*s\n", ACTIONS_NUM_PRINT_WIDTH, com, ACTIONS_PRINT_WIDTH, "Умножить матрицу на вектор столбец."), com++;
    // 12
    printf("~ %*d - %-*s\n", ACTIONS_NUM_PRINT_WIDTH, com, ACTIONS_PRINT_WIDTH, "Вывести произведение матрицы на вектор столбец. <БЕЗ ИЗМЕНЕНИЯ> <РАЗРЕЖЕННАЯ МАТРИЦА>"), com++;

    printf("\n");

    // 13
    printf("~ %*d - %-*s\n", ACTIONS_NUM_PRINT_WIDTH, com, ACTIONS_PRINT_WIDTH, "Сравнить время выполнения стандартного алгоритма"), com++;
        printf("~ %-*s   %-*s\n", ACTIONS_NUM_PRINT_WIDTH, " ", ACTIONS_PRINT_WIDTH, "и алгоритма обработки разреженных матриц.");

    printf("\n");

    // 14
    printf("~ %*d - %-*s\n", ACTIONS_NUM_PRINT_WIDTH, com, ACTIONS_PRINT_WIDTH, "Сравнить объем требуемой памяти для реализации стандартного алгоритма"), com++;
        printf("~ %-*s   %-*s\n", ACTIONS_NUM_PRINT_WIDTH, " ", ACTIONS_PRINT_WIDTH, "обработки матриц и алгоритма обработки разреженных матриц.");

    printf("\n");

    // 15
    printf("~ %*d - %-*s\n", ACTIONS_NUM_PRINT_WIDTH, com, ACTIONS_PRINT_WIDTH, "Сгенерировать матрицу с заданной разреженностью."), com++;
}

int actions_handler(int com, sparse_matrix_t *sprs, matrix_t *m)
{
    switch (com)
    {
    case 0:
        break;
    case 1:
        return exec_input(sprs, m, 0, stdin);
    case 2:
        return exec_input(sprs, m, 0, stderr);
    case 3:
        return exec_input(sprs, m, 1, stdin);
    case 4:
        return exec_input(sprs, m, 1, stderr);
    case 5:
        return exec_output(sprs, 1, 0, stdout);
    case 6:
        return exec_output(sprs, 1, 1, stdout);
    case 7:
        return exec_output(sprs, 0, 0, stdout);
    case 8:
        return exec_output(sprs, 0, 1, stdout);
    case 9:
        return exec_output(sprs, 1, 0, stderr);
    case 10:
        return exec_output(sprs, 1, 1, stderr);
    case 11:
        return exec_prod(sprs, m, 0);
    case 12:
        return exec_prod(sprs, m, 1);
    case 13:
        exec_time_compare(sparsem_col_prod_time);
        exec_time_compare(matrix_col_prod_time);
        break;
    case 14:
        exec_mem_compare(sprs, m);
        break;
    case 15:
        return exec_generate(sprs);
    default:
        break;
    }

    return EXIT_SUCCESS;
}

int exec_input(sparse_matrix_t *sprs, matrix_t *m, int type, FILE *stream)
{
    int rc = 0;

    if (stream != stdin)
    {
        printf("Введите название файла: ");
        char fname[BUFFER_LEN];
        if ((rc = input_str(stdin, fname)))
            return rc;
        
        stream = fopen(fname, "r");
        if (stream == NULL)
            return EXIT_INCORRECT_FILENAME;
    }

    if (type)
    {
        if ((rc = matrix_scan(m, stream)))
            return rc;

        sparsem_from_matrix(sprs, m);

        printf("\n\t! Матрица успешно введена!\n");
    }
    else
    {
        if ((rc = sparsem_scan(sprs, stream)))
            return rc;

        sparsem_to_matrix(sprs, m);
        
        printf("\n\t! Разреженная матрица успешно введена!\n");
    }

    if (stream != stdin)
        fclose(stream);

    return EXIT_SUCCESS;
}

int exec_output(sparse_matrix_t *sprs, int zeros, int format, FILE *stream)
{
    int rc = 0;

    if (stream != stdout)
    {
        printf("Введите название файла: ");
        char fname[BUFFER_LEN];
        if ((rc = input_str(stdin, fname)))
            return rc;
        
        stream = fopen(fname, "w");
        if (stream == NULL)
            return EXIT_INCORRECT_FILENAME;
    }

    if (zeros)
    {
        matrix_t m;
        sparsem_to_matrix(sprs, &m);
        matrix_print(&m, format, stream);
    }
    else
        sparsem_print_matrix(sprs, zeros, format, stream);

    if (stream != stdout)
    {
        fclose(stream);
        printf("\n\t! Матрица успешно записана в файл!\n");
    }

    return EXIT_SUCCESS;
}

int exec_prod(sparse_matrix_t *sprs, matrix_t *m, int copy)
{
    int rc = 0;

    vector_col_t v_col;
    printf("Введите вектор-столбец (через пробел): ");
    if ((rc = input_ints(stdin, v_col.data, &(v_col.size), ROWS_SIZE, " ")))
        return rc;

    sparse_matrix_t result;

    if ((rc = sparsem_column_prod(sprs, &v_col, &result)))
        return rc;

    if (copy)
        sparsem_print_matrix(&result, 0, 0, stdout);
    else
    {
        *sprs = result;
        sparsem_to_matrix(sprs, m);
        printf("\n\t! Умножение матрицы на вектор-столбец успешно выполнено!\n");
    }
    
    return EXIT_SUCCESS;
}

int exec_generate(sparse_matrix_t *sprs)
{
    int rc = 0;

    printf("Введите размеры матрицы (Количество_Строк Количество_Столбцов): ");
    matrix_t m;
    if ((rc = matrix_size_scan(&(m.col_size), &(m.row_size), stdin)))
        return rc;

    int sparsity;
    printf("Введите процент заполнения матрицы нулями: ");
    if ((rc = input_int(stdin, &sparsity)))
        return rc;

    matrix_generate(&m, sparsity);
    sparsem_from_matrix(sprs, &m);
    printf("\n\t! Матрица успешно сгенерирована и записана!\n");

    return EXIT_SUCCESS;
}

void print_nsyms(int n, char c, char end)
{
    for (int i = 0; i < n; i++)
        printf("%c", c);

    printf("%c", end);
}

void exec_time_compare(unsigned long long (*method)(void *, vector_col_t *, void *))
{
    int max_sz = 100;
    int max_sparsity = 100;

    int cell_width = 10;
    int table_width = (12) * cell_width + cell_width + 3;

    vector_col_t v_col;
    v_col.size = max_sz;
    for (size_t i = 0; i < v_col.size; i++)
        v_col.data[i] = 1;

    print_nsyms(table_width, '_', '\n');
    char *s = "Default matrix";
    if (method == sparsem_col_prod_time)
        s = "Sparse matrix";
    printf("|%*s|\n", table_width - 2, s);

    print_nsyms(table_width, '_', '\n');

    printf("|%*s", cell_width, "SIZE\\SPRS");
    for (int sparsity = 0; sparsity <= max_sparsity; sparsity += 10)
    {
        printf("|%*d", cell_width, sparsity);
    }
    printf("|\n");

    print_nsyms(table_width, '_', '\n');

    for (int sz = 10; sz <= max_sz; sz += 90)
    {
        v_col.size = sz;

        printf("|%*d", cell_width, sz);
        for (int sparsity = 0; sparsity <= max_sparsity; sparsity += 10)
        {
            char fname[50];
            sprintf(fname, "./rand/data_%d_%d.txt", sz, sparsity);

            FILE *f_in = fopen(fname, "r");
            if (f_in != NULL)
            {
                vector_col_t res1;
                matrix_t data;
                matrix_scan(&data, f_in);
                fclose(f_in);

                void *matrix = &data;
                void *result = &res1;

                if (method == sparsem_col_prod_time)
                {
                    sparse_matrix_t res2;
                    result = &res2;
                    sparsem_from_matrix((sparse_matrix_t *)matrix, &data);
                }

                printf("|%*llu", cell_width, method(matrix, &v_col, result));
            }
        }
        printf("|\n");
        print_nsyms(table_width, '_', '\n');
    }

    printf("\n");
}

void exec_mem_compare(sparse_matrix_t *sprs, matrix_t *m)
{
    int cell_width = 10;
    int table_width = cell_width * 2 + 3;

    print_nsyms(table_width, '_', '\n');
    printf("|%*s|%*s|\n", cell_width, "Sparse", cell_width, "Default");
    print_nsyms(table_width, '_', '\n');
    printf("|%*lu|%*lu|\n", cell_width, sizeof(*sprs), cell_width, sizeof(*m));
    print_nsyms(table_width, '_', '\n');
}