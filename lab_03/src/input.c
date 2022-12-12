#include "input.h"

int input_str(FILE *stream, char str[BUFFER_LEN])
{
    char buff[BUFFER_LEN];
    if (fgets(buff, BUFFER_LEN, stream) == NULL)
        return EXIT_INCORRECT_INPUT;

    int buff_len = strlen(buff);
    if (buff[buff_len - 1] != '\n')
        return EXIT_INPUT_OVERFLOW;
    buff[buff_len - 1] = '\0';

    strcpy(str, buff);

    return EXIT_SUCCESS;
}

int input_ints(FILE *stream, int data[], size_t *size, size_t size_max, char *delim)
{
    *size = 0;

    char buff[BUFFER_LEN];
    if (fgets(buff, BUFFER_LEN, stream) == NULL)
        return EXIT_INCORRECT_INPUT;

    int buff_len = strlen(buff);
    if (buff[buff_len - 1] != '\n')
        return EXIT_INPUT_OVERFLOW;
    buff[buff_len - 1] = '\0';

    for (char *cur_num = strtok(buff, delim); cur_num != NULL; cur_num = strtok(NULL, delim))
    {
        if (*size == size_max)
            return EXIT_DATA_OVERFLOW;

        (*size)++;   
        if (sscanf(cur_num, "%d", &(data[*size - 1])) != 1)
            return EXIT_INCORRECT_ELEMENT;
    }

    return EXIT_SUCCESS;
}

int input_size(FILE *stream, size_t *data)
{
    char buff[BUFFER_LEN];
    if (fgets(buff, BUFFER_LEN, stream) == NULL)
        return EXIT_INCORRECT_INPUT;

    int buff_len = strlen(buff);
    if (buff[buff_len - 1] != '\n')
        return EXIT_INPUT_OVERFLOW;
    buff[buff_len - 1] = '\0';

    if (sscanf(buff, "%zu", data) != 1)
        return EXIT_INCORRECT_ELEMENT;

    return EXIT_SUCCESS;
}

int input_int(FILE *stream, int *data)
{
    char buff[BUFFER_LEN];
    if (fgets(buff, BUFFER_LEN, stream) == NULL)
        return EXIT_INCORRECT_INPUT;

    int buff_len = strlen(buff);
    if (buff[buff_len - 1] != '\n')
        return EXIT_INPUT_OVERFLOW;
    buff[buff_len - 1] = '\0';

    if (sscanf(buff, "%d", data) != 1)
        return EXIT_INCORRECT_ELEMENT;

    return EXIT_SUCCESS;
}
