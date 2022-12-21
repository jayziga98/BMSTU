#include "my_time.h"

unsigned long long nanoseconds(const struct timespec *beg, const struct timespec *end)
{
    unsigned long long sec_to_n = (end->tv_sec - beg->tv_sec) * 1000000000ULL;
    unsigned long long nano_sec = (end->tv_nsec - beg->tv_nsec) * 1ULL;
    return sec_to_n + nano_sec;
}

unsigned long long func_exec_time(void (*exec_func)())
{
    struct timespec beg, end;

    clock_gettime(CLOCK_MONOTONIC_RAW, &beg);
    exec_func();
    clock_gettime(CLOCK_MONOTONIC_RAW, &end);

    return nanoseconds(&beg, &end);
}
