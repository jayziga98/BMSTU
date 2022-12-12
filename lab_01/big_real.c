#include "big_real.h"

int breal_scan(big_real_t *num)
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
        return EXIT_NOT_INPUT_BIG_REAL;

    breal_init(num);

    if (input[0] == '-')
        num->m_sign = '-';
    
    size_t e_pos = INPUT_LEN;
    int is_significant = 0;
    for (size_t i = (input[0] == '+' || input[0] == '-' ? 1 : 0); i < input_len; i++)
        if (input[i] == '.' && num->dot_pos == MANTISSA_SIZE)
        {
            num->dot_pos = num->m_size;
            is_significant = 1;
        }
        else if (isdigit(input[i]))
        {
            if (is_significant || input[i] != '0')
            {
                is_significant = 1;
                num->m_size++;
                if (num->m_size > MANTISSA_SIZE)
                    return EXIT_MANTISSA_OVERFLOW;
                num->mantissa[num->m_size - 1] = input[i] - '0';
            }
        }
        else if (tolower(input[i]) == 'e' && e_pos == INPUT_LEN)
        {
            e_pos = i;
            break;
        }
        else
            return EXIT_INCORRECT_SYMBOLS;

    if (num->dot_pos == MANTISSA_SIZE)
        num->dot_pos = num->m_size;

    int exp_sign = 1;
    if (input[e_pos + 1] == '-' || input[e_pos + 1] == '+')
    {
        e_pos++;
        exp_sign = (input[e_pos] == '-' ? -1 : 1);
    }

    for (size_t i = e_pos + 1; i < input_len; i++)
        if (isdigit(input[i]))
        {
            num->exponent = num->exponent * BREAL_BASE + input[i] - '0';
            if (EXPONENT_MAX < num->exponent || EXPONENT_MIN > num->exponent)
                return EXIT_EXPONENT_OVERFLOW;
        }
        else
            return EXIT_INCORRECT_SYMBOLS;
        
    num->exponent *= exp_sign;

    return EXIT_SUCCESS;
}

void breal_init(big_real_t *num)
{
    num->dot_pos = MANTISSA_SIZE;
    num->exponent = 0;
    num->m_sign = '+';
    num->m_size = 0;
    for (size_t i = 0; i < MANTISSA_SIZE; i++)
        num->mantissa[i] = 0;
    num->normalized = 0;
}

// Убирает из мантиссы непрерывную последовательтность цифр равных digit с позиции beg
// Возвращает длину последовательности
size_t breal_del_identseq(big_real_t *num, size_t beg, int digit)
{
    size_t size = beg;
    size_t cnt = 0;
    int flag = 1;
    for (size_t i = beg; i < num->m_size; i++)
        if (num->mantissa[i] == digit && flag)
            cnt++;
        else
        {
            flag = 0;
            size++;
            num->mantissa[size - 1] = num->mantissa[i];
        }

    num->m_size = size;
    if (beg < num->dot_pos)
        num->dot_pos -= cnt + (beg + cnt > num->dot_pos ? beg + cnt - num->dot_pos : 0);

    return cnt;
}

size_t breal_last_significant(big_real_t *num)
{
    for (size_t i = num->m_size; i > 0; i--)
        if (num->mantissa[i - 1])
            return i;
    
    return num->m_size;
}

// Приводит число к нормальному виду:
// Прим: -0.123456+E123
int breal_normalize(big_real_t *num)
{
    if (!num->normalized)
    {
        num->exponent += num->dot_pos;
        num->dot_pos = 0;
        num->exponent -= breal_del_identseq(num, num->dot_pos, 0);
        //breal_del_identseq(num, 0, 0);
        breal_del_identseq(num, breal_last_significant(num), 0);

        if (EXPONENT_MAX < num->exponent || EXPONENT_MIN > num->exponent)
            return EXIT_EXPONENT_OVERFLOW;

        if (num->m_size == 0 || (num->m_size == 1 && num->mantissa[0] == 0))
            num->exponent = 0;

        num->normalized = 1;
    }

    return EXIT_SUCCESS;
}

void breal_print(big_real_t *num)
{
    printf("%c", num->m_sign);
    if (num->dot_pos == 0)
        printf("0");
    if (num->m_size == 0)
        printf(".0");
    for (size_t i = 0; i < num->m_size; i++)
    {
        if (i == num->dot_pos)
            printf(".");
        printf("%d", num->mantissa[i]);
    }

    printf("E");
    if (num->exponent >= 0)
        printf("+");
    printf("%d\n", num->exponent);
}

int breal_sum(big_real_t *num1, big_real_t *num2, big_real_t *result)
{
    breal_init(result);

    int addition = 0;
    for (size_t i1 = num1->m_size, i2 = num2->m_size; i1 || i2 || addition; i1--, i2--)
    {
        int d1 = 0, d2 = 0;
        if (i1)
            d1 = num1->mantissa[i1 - 1];
        if (i2)
            d2 = num2->mantissa[i2 - 1];

        int temp = (d1 + d2 + addition);

        result->m_size++;
        if (result->m_size > MANTISSA_SIZE)
            return EXIT_MANTISSA_OVERFLOW;

        result->mantissa[result->m_size - 1] = temp % BREAL_BASE;
        addition = temp / BREAL_BASE;
    }

    breal_reverse_mantissa(result);

    return EXIT_SUCCESS;
}

void breal_reverse_mantissa(big_real_t *num)
{
    for (size_t i = 0; i < num->m_size / 2; i++)
        char_swap(&num->mantissa[i], &num->mantissa[num->m_size - i - 1]);
}
