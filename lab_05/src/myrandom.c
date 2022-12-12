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
