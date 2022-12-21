#include "queuing_system.h"

double qsystem_request_arrival_time()
{
    return rand_double_from(REQUEST_ARRIVAL_TIME_MIN, REQUEST_ARRIVAL_TIME_MAX);
}

int qsystem_request_new(queuing_system_t *qsys, double time, int (*add)(queue_t, int, int), int addrs)
{
    int rc = 0;

    qsys->exec_time += time;

    if ((rc = add(qsys->q, 0, addrs)))
        return rc;
    qsys->q_len++;

    qsys->cnt_req_in++;

    return EXIT_SUCCESS;
}

int qsystem_request_handle(queuing_system_t *qsys, double *time, int (*add)(queue_t, int, int), int (*pop)(queue_t, int *, int), int addrs)
{
    int rc = 0;

    int elem;
    if ((rc = pop(qsys->q, &elem, addrs)))
        return EXIT_FAILURE;
    qsys->q_len--;

    double handle_time = rand_double_from(SERVICE_TIME_MIN, SERVICE_TIME_MAX);

    *time = handle_time;

    qsys->unit.exec_time += handle_time;
    qsys->unit.runs++;

    elem++;

    if (elem == SERVICE_CYCLE_CNT)
        qsys->cnt_req_out++;
    else
    {
        if ((rc = add(qsys->q, elem, addrs)))
            return rc;
        qsys->q_len++;
    }

    return EXIT_SUCCESS;
}

void qsystem_init(queuing_system_t *qsys, queue_t q)
{
    qsys->cnt_req_in = 0;
    qsys->cnt_req_out = 0;
    qsys->exec_time = 0;
    qsys->unit.exec_time = 0;
    qsys->unit.runs = 0;
    qsys->q = q;
    qsys->q_len = 0;
}

int qsystem_simulate(queuing_system_t *qsys, int addrs, queue_t q, int (*create)(queue_t, size_t), int (*add)(queue_t, int, int), int (*pop)(queue_t, int *, int), void (*clear)(queue_t, int), size_t n_reqs_out, int info)
{
    int rc = 0;

    qsystem_init(qsys, q);

    if (create != NULL && (rc = create(qsys->q, n_reqs_out * SERVICE_TIME_MAX)))
        return rc;

    size_t q_len_sum = 0;
    size_t col = 0;

    double time_arrival = qsystem_request_arrival_time();
    double time_handle_sum = 0.0;
    while (qsys->cnt_req_out != n_reqs_out)
    {
        double time_handle;
        if (qsys->q_len && (rc = qsystem_request_handle(qsys, &time_handle, add, pop, addrs)))
            return rc;
        time_handle_sum += time_handle;

        if (info && qsys->cnt_req_out && !(qsys->cnt_req_out % QS_INFO_PRINT_PERIOD))
        {
            col++;
            q_len_sum += qsys->q_len;
            printf("| Текущая длина очереди : %zu | Средняя длина очереди: %zu |\n", qsys->q_len, q_len_sum / col);
        }

        if (time_handle_sum >= time_arrival || !qsys->q_len)
        {
            if ((rc = qsystem_request_new(qsys, time_arrival, add, addrs)))
                return rc;

            if (time_handle_sum >= time_arrival)
                time_handle_sum = time_handle_sum - time_arrival;

            time_arrival = qsystem_request_arrival_time();
        }
    }

    clear(qsys->q, addrs);

    return EXIT_SUCCESS;
}

unsigned long long qsystem_simulate_time(int type)
{
    unsigned long long sum = 0;

    for (int i = 0; i < TIME_RUNS; i++)
    {
        struct timespec beg, end;

        queue_linked_list_t qll;
        queue_linked_list_init(&qll);
        queue_std_t q;
        queuing_system_t qsys;

        if (type == 1)
        {
            clock_gettime(CLOCK_MONOTONIC_RAW, &beg);   
            qsystem_simulate(&qsys, 0, &q, queuestd_create, queuestd_add, queuestd_pop, queuestd_clear, REQS_OUT, 0);
            clock_gettime(CLOCK_MONOTONIC_RAW, &end);
        }
        else if (type == 2)
        {
            clock_gettime(CLOCK_MONOTONIC_RAW, &beg);
            qsystem_simulate(&qsys, 0, &qll, NULL, queue_linked_list_add, queue_linked_list_pop, queue_linked_list_clear, REQS_OUT, 0);
            clock_gettime(CLOCK_MONOTONIC_RAW, &end);
        }

        sum += nanoseconds(&beg, &end);
    }

    return sum / TIME_RUNS;
}
