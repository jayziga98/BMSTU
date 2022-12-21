#include "big_int.h"

int bint_scan(big_int_t *num)
{
    char input[INPUT_LEN];

    if (fgets(input, INPUT_LEN, stdin) == NULL)
        return EXIT_EMPTY_INPUT;

    size_t input_len = strlen(input);

    if (input[input_len - 1] != '\n')
        return EXIT_INPUT_OVERFLOW;
    input[input_len - 1] = '\0';
    input_len--;
    if (!input_len)
        return EXIT_NOT_INPUT_BIG_INT;

    num->sign = '+';
    if (input[0] == '-')
        num->sign = '-';

    int is_significant = 0;
    num->size = 0;
    for (size_t i = (input[0] == '+' || input[0] == '-' ? 1 : 0); i < input_len; i++)
        if (isdigit(input[i]))
        {
            if ((is_significant || input[i] != '0'))
            {
                is_significant = 1;
                num->size++;
                if (num->size > BIG_INT_SIZE)
                    return EXIT_BIG_INT_OVERFLOW;
                num->digits[num->size - 1] = input[i] - '0';
            }
        }
        else
            return EXIT_INCORRECT_SYMBOLS;

    return EXIT_SUCCESS;
}

void bint_print(big_int_t *num)
{
    printf("%c", num->sign);

    for (size_t i = 0; i < num->size; i++)
        printf("%d", num->digits[i]);

    printf("\n");
}
