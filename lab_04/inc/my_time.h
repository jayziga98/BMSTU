#ifndef __MY_TIME_H__

#define __MY_TIME_H__

#include <stdio.h>
#include <stdlib.h>
#include <sys/time.h>
#include <time.h>

#define TIME_RUNS 1000

unsigned long long nanoseconds(const struct timespec *beg, const struct timespec *end);
unsigned long long func_exec_time(void (*exec_func)());

#endif // #ifndef __MY_TIME_H__
