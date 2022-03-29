#define  _GNU_SOURCE
#include <sched.h>
#include <stdio.h>
#include <unistd.h>

int main(int argc, char const *argv[]) {
    int cpuID;
    long cpuNo;
    cpu_set_t mask;

    int policy;
    struct sched_param param, param2;

    // showing which cpu is using
    cpuID = sched_getcpu();
    printf("At first, CPU ID: %d\n", cpuID);

    // showing no of cpu avaiable in the pc
    cpuNo = sysconf(_SC_NPROCESSORS_ONLN);
    printf("No. available of CPUS: %ld\n", cpuNo);

    // showing available cpu
    printf("Available CPUS are:\n");
    sched_getaffinity(0, sizeof(cpu_set_t), &mask);
    for (int i = 0; i < cpuNo; i++) {
        printf("%d ", CPU_ISSET(i, &mask));
    }
    printf("\n");

    CPU_ZERO(&mask);
    CPU_SET(2, &mask);
    sched_setaffinity(0, sizeof(cpu_set_t), &mask);

    //sched_getaffinity(0, sizeof(cpu_set_t), &mask);
    printf("After selecting CPU-2\n");
    printf("Now Available CPU is:\n");
    for (int i = 0; i < cpuNo; i++) {
        printf("%d ", CPU_ISSET(i, &mask));
    }
    printf("\n");

    cpuID = sched_getcpu();
    printf("CPU ID: %d\n", cpuID);

    policy = sched_getscheduler(0);
    printf("Scheduling Policy: %d\n", policy);
    printf("SCHED_OTHER = %d, SCHED_BATCH = %d, SCHED_IDLE = %d, SCHED_FIFO = %d, SCHED_RR = %d\n", SCHED_OTHER, SCHED_BATCH, SCHED_IDLE, SCHED_FIFO, SCHED_RR);

    // printf("Minimum Priority of SCHED_OTHER: %d\n", sched_get_priority_min(SCHED_OTHER));
    // printf("Maximum Priority of SCHED_OTHER: %d\n", sched_get_priority_max(SCHED_OTHER));
    //
    // printf("Minimum Priority of SCHED_OTHER: %d\n", sched_get_priority_min(SCHED_FIFO));
    // printf("Maximum Priority of SCHED_OTHER: %d\n", sched_get_priority_max(SCHED_FIFO));

    param.sched_priority = 34;
    sched_setscheduler(0, SCHED_FIFO, &param);
    sched_getparam(0, &param2);
    printf("Scheduling Policy: %d\n", policy);
    printf("Scheduling Priority: %d\n", param2.sched_priority);

    return 0;
}
