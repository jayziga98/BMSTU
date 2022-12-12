#include "big_nums_operations.h"

int bnumsop_multiply(big_real_t *num1, big_int_t *num2, big_real_t *result)
{
    breal_normalize(num1);
    
    int rc = 0;

    temp_t cur_sum;
    cur_sum.size = 0;

    temp_t last_addendum;
    last_addendum.size = 0;
    for (size_t i2 = num2->size; i2; i2--)
    {
        temp_t cur_addendum;
        cur_addendum.size = 0;

        int addition = 0;
        for (size_t i1 = num1->m_size; i1 || addition; i1 -= (i1 ? 1 : 0))
        {
            int temp = (num1->mantissa[i1 - 1] * num2->digits[i2 - 1] + addition);

            cur_addendum.size++;
            if (cur_addendum.size > TEMP_SIZE)
                return EXIT_MANTISSA_OVERFLOW;

            cur_addendum.data[cur_addendum.size - 1] = temp % BREAL_BASE;
            addition = temp / BREAL_BASE;
        }
        temp_reverse(&cur_addendum);

        for (size_t i = 0; i < num2->size - i2; i++)
        {
            cur_addendum.size++;
            cur_addendum.data[cur_addendum.size - 1] = 0;
        }

        if (num2->size == 1)
            cur_sum = cur_addendum;
        else if (i2 == num2->size)
            last_addendum = cur_addendum;
        else
        {
            if ((rc = temp_sum(&last_addendum, &cur_addendum, &cur_sum)))
                return rc;
            last_addendum = cur_sum;
        }
    }

    result->dot_pos = 0;
    result->exponent = num1->exponent;
    result->m_sign = (num1->m_sign == num2->sign ? '+' : '-');
    result->normalized = 0;
    if (num1->m_size < cur_sum.size)
        result->exponent += cur_sum.size - num1->m_size;
    bnumsop_copy(&cur_sum, result);

    breal_normalize(result);

    if (EXPONENT_MAX < result->exponent || EXPONENT_MIN > result->exponent)
            return EXIT_EXPONENT_OVERFLOW;

    return EXIT_SUCCESS;
}

void bnumsop_copy(temp_t *src, big_real_t *dst)
{ 
    dst->exponent += bnumsop_round(src, MANTISSA_SIZE);
    dst->m_size = 0;
    
    for (size_t i = 0; i < src->size; i++, dst->m_size++)
        dst->mantissa[i] = src->data[i];
}

int bnumsop_round(temp_t *src, size_t rank)
{
    int cnt = 0;

    if (src->size > rank)
    {
        char addition = (src->data[src->size - 1] >= 5);
        src->size--;

        for (; src->size; src->size--)
            if (src->size <= rank)
            {
                if (!addition)
                    break;
                src->data[src->size - 1] += addition;
                addition = (src->data[src->size - 1] >= 5); 
            }
            else
            {
                src->data[src->size - 1] += addition;
                addition = (src->data[src->size - 1] >= 5); 
                cnt--;
            }

        if (!src->size)
            src->size++;

    }

    return cnt;
}

void temp_reverse(temp_t *temp)
{
    for (size_t i = 0; i < temp->size / 2; i++)
        char_swap(&temp->data[i], &temp->data[temp->size - i - 1]);
}

int temp_sum(temp_t *temp1, temp_t *temp2, temp_t *result)
{
    result->size = 0;

    char addition = 0;
    for (size_t i1 = temp1->size, i2 = temp2->size; i1 || i2 || addition; i1 -= (i1 ? 1 : 0), i2 -= (i2 ? 1 : 0))
    {
        int d1 = 0, d2 = 0;
        if (i1)
            d1 = temp1->data[i1 - 1];
        if (i2)
            d2 = temp2->data[i2 - 1];

        int temp = (d1 + d2 + addition);
        result->size++;
        if (result->size > TEMP_SIZE)
            return EXIT_MANTISSA_OVERFLOW;

        result->data[result->size - 1] = temp % BNUMSOP_BASE;
        addition = temp / BNUMSOP_BASE;
    }

    temp_reverse(result);

    return EXIT_SUCCESS;
}

void temp_print(temp_t *temp)
{
    for (size_t i = 0; i < temp->size; i++)
        printf("%d", temp->data[i]);

    printf("\n");
}
