#include "myrandom.h"

void set_seed()
{
    srand(time(NULL));
}

double rand_double_from(double min, double max) 
{
    double range = (max - min); 
    double div = RAND_MAX / range;
    return min + (rand() / div);
}

int rand_int_from(int min, int max)
{
    int range = (max - min);
    int div = RAND_MAX / range;
    return min + (rand() / div);
}

size_t rand_size_from(size_t min, size_t max)
{
    size_t range = (max - min);
    size_t div = RAND_MAX / range;
    return min + (rand() / div);
}