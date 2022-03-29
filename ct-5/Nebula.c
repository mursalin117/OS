#define _GNU_SOURCE
#include <pthread.h>
#include <stdio.h>
#include <unistd.h>
#include <sys/syscall.h>

void thread1 () {
    pid_t pid, tid;
    int cpuNo, policy;
    struct sched_param param, param2;

    pid = getpid();
    tid = syscall(SYS_gettid);
    cpuNo = sched_getcpu();
    printf("Nebula: Thread-X (PID: %d, TID: %d CPU: %d).\n", pid, tid, cpuNo);

    policy = sched_getscheduler(0);
    printf("Scheduling Policy: %d\n", policy);
    printf("SCHED_OTHER = %d, SCHED_BATCH = %d, SCHED_IDLE = %d, SCHED_FIFO = %d, SCHED_RR = %d\n", SCHED_OTHER, SCHED_BATCH, SCHED_IDLE, SCHED_FIFO, SCHED_RR);

    param.sched_priority = 34;
    sched_setscheduler(0, SCHED_FIFO, &param);
    sched_getparam(0, &param2);
    printf("Scheduling Policy: %d\n", policy);
    printf("Scheduling Priority: %d\n", param2.sched_priority);
}

void thread2 () {
    pid_t pid, tid;
    int cpuNo, policy;
    struct sched_param param, param2;

    pid = getpid();
    tid = syscall(SYS_gettid);
    cpuNo = sched_getcpu();
    printf("Nebula: Thread-Y (PID: %d, TID: %d CPU: %d).\n", pid, tid, cpuNo);

    policy = sched_getscheduler(0);
    printf("Scheduling Policy: %d\n", policy);
    printf("SCHED_OTHER = %d, SCHED_BATCH = %d, SCHED_IDLE = %d, SCHED_FIFO = %d, SCHED_RR = %d\n", SCHED_OTHER, SCHED_BATCH, SCHED_IDLE, SCHED_FIFO, SCHED_RR);

    param.sched_priority = 34;
    sched_setscheduler(0, SCHED_FIFO, &param);
    sched_getparam(0, &param2);
    printf("Scheduling Policy: %d\n", policy);
    printf("Scheduling Priority: %d\n", param2.sched_priority);
}

int main(int argc, char const *argv[]) {
    int i;
    pthread_t x, y;

    for (i = 0; i < 10; i++) {

        pthread_create(&x, NULL, (void *)thread1, NULL);
        pthread_create(&y, NULL, (void *)thread2, NULL);
    }

    pthread_join(x, NULL);
    pthread_join(y, NULL);

    return 0;
}
