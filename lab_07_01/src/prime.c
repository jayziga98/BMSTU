#include "prime.h"

int prime_is_prime(int num)
{
    for (int i = 2; i * i <= num; i++)
        if (!(num % i))
            return 0;

    return 1;
}

int prime_next(int num)
{
    for (num++; !prime_is_prime(num); num++);

    return num;
}