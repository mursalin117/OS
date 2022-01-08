#define _GNU_SOURCE
#include <stdio.h>
#include <sched.h>

int main(int argc, char const *argv[]) {
    int policy;
    struct sched_param param;

    policy = sched_getscheduler(0);
    printf("Scheduling Policy: %d\n", policy);
    printf("%d, %d, %d, %d, %d\n", SCHED_OTHER, SCHED_BATCH, SCHED_IDLE, SCHED_FIFO, SCHED_RR);

    printf("Minimum Priority of SCHED_OTHER: %d\n", sched_get_priority_min(SCHED_OTHER));
    printf("Maximum Priority of SCHED_OTHER: %d\n", sched_get_priority_max(SCHED_OTHER));

    printf("Minimum Priority of SCHED_OTHER: %d\n", sched_get_priority_min(SCHED_FIFO));
    printf("Maximum Priority of SCHED_OTHER: %d\n", sched_get_priority_max(SCHED_FIFO));

    param.sched_priority = 34;
    sched_setscheduler(0, SCHED_FIFO, &param);
    printf("Scheduling Policy: %d\n", policy);
    printf("Scheduling Priority: %d\n", get_priority());

    return 0;
}
