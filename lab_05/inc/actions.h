#ifndef __ACTIONS_H__

#define __ACTIONS_H__

#include <stdio.h>
#include <stdlib.h>

#include "linked_list_queue.h"
#include "queue.h"
#include "queuing_system.h"

#define COMMAND_NUMBER_LEN 3

void info_print();
int actions_print();
int actions_handler(int com, queuing_system_t *qsys, queue_std_t *q, queue_linked_list_t *qll);
void exec_simulate(int type, queuing_system_t *qsys, queue_std_t *q, queue_linked_list_t *qll);
void exec_time_cmp();
void exec_mem_cmp();

#endif // #ifndef __ACTIONS_H__
