#include "char_utils.h"

void char_swap(char *c1, char *c2)
{
    char temp = *c1;
    *c1 = *c2;
    *c2 = temp;
}
