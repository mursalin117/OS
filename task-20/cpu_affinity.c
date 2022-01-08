#define  _GNU_SOURCE
#include <sched.h>
#include <stdio.h>
#include <unistd.h>

int main(int argc, char const *argv[]) {
    int cpuID;
    long cpuNo;
    cpu_set_t mask;

    // showing which cpu is using
    cpuID = sched_getcpu();
    printf("CPU ID: %d\n", cpuID);

    // showing no of cpu avaiable in the pc
    cpuNo = sysconf(_SC_NPROCESSORS_ONLN);
    printf("No. of CPUS: %ld\n", cpuNo);

    // showing available cpu
    sched_getaffinity(0, sizeof(cpu_set_t), &mask);
    for (int i = 0; i < cpuNo; i++) {
        printf("%d ", CPU_ISSET(i, &mask));
    }
    printf("\n");

    CPU_ZERO(&mask);
    CPU_SET(2, &mask);
    sched_setaffinity(0, sizeof(cpu_set_t), &mask);

    //sched_getaffinity(0, sizeof(cpu_set_t), &mask);
    for (int i = 0; i < cpuNo; i++) {
        printf("%d ", CPU_ISSET(i, &mask));
    }
    printf("\n");

    cpuID = sched_getcpu();
    printf("CPU ID: %d\n", cpuID);

    return 0;
}
