#ifndef __QUEUING_SYSTEM_H__

#define __QUEUING_SYSTEM_H__

#include <stdio.h>
#include <stdlib.h>

#include "queue.h"
#include "linked_list_queue.h"

#include "myrandom.h"
#include "my_time.h"

#define SERVICE_CYCLE_CNT 5

#define SERVICE_TIME_MIN 0
#define SERVICE_TIME_MAX 1

#define REQUEST_ARRIVAL_TIME_MIN 0
#define REQUEST_ARRIVAL_TIME_MAX 4

#define QS_INFO_PRINT_PERIOD 100

#define REQS_OUT 1000

typedef void* queue_t;

typedef struct
{
    int runs;
    double exec_time;
} maintenance_unit_t;

typedef struct
{
    maintenance_unit_t unit;
    queue_t q;
    size_t q_len;
    size_t cnt_req_in;
    size_t cnt_req_out;
    double exec_time;
} queuing_system_t;

double qsystem_request_arrival_time();
int qsystem_request_new(queuing_system_t *qsys, double time, int (*add)(queue_t, int, int), int addrs);
int qsystem_request_handle(queuing_system_t *qsys, double *time, int (*add)(queue_t, int, int), int (*pop)(queue_t, int *, int), int addrs);
void qsystem_init(queuing_system_t *qsys, queue_t q);
int qsystem_simulate(queuing_system_t *qsys, int addrs, queue_t q, int (*create)(queue_t, size_t), int (*add)(queue_t, int, int), int (*pop)(queue_t, int *, int), void (*clear)(queue_t, int), size_t n_reqs_out, int info);
unsigned long long qsystem_simulate_time(int type);

#endif // #ifndef __QUEUING_SYSTEM_H__
