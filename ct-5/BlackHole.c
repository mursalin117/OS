#define _GNU_SOURCE
#include <pthread.h>
#include <stdio.h>
#include <unistd.h>
#include <sys/syscall.h>

pthread_mutex_t key;

void thread1 () {
    pthread_mutex_lock(&key);

    pid_t pid, tid;
    int cpuID;
    long cpuNo;
    cpu_set_t mask;

    pid = getpid();
    tid = syscall(SYS_gettid);
    cpuNo = sched_getcpu();
    printf("BlackHole: Thread-X (PID: %d, TID: %d).\n", pid, tid);

    // showing which cpu is using
    cpuID = sched_getcpu();
    printf("[BlackHole-X] At first, CPU ID: %d\n", cpuID);

    // showing no of cpu avaiable in the pc
    cpuNo = sysconf(_SC_NPROCESSORS_ONLN);
    printf("[BlackHole-X] No. of available CPUS: %ld\n", cpuNo);

    // showing available cpu
    printf("[BlackHole-X] Available CPUS are:\n");
    sched_getaffinity(0, sizeof(cpu_set_t), &mask);
    for (int i = 0; i < cpuNo; i++) {
        printf("%d ", CPU_ISSET(i, &mask));
    }
    printf("\n");

    CPU_ZERO(&mask);
    CPU_SET(2, &mask);
    sched_setaffinity(0, sizeof(cpu_set_t), &mask);

    //sched_getaffinity(0, sizeof(cpu_set_t), &mask);
    printf("[BlackHole-X] After selecting CPU-2\n");
    printf("[BlackHole-X] Now Available CPU is:\n");
    for (int i = 0; i < cpuNo; i++) {
        printf("%d ", CPU_ISSET(i, &mask));
    }
    printf("\n");

    cpuID = sched_getcpu();
    printf("[BlackHole-X] Now CPU ID: %d\n", cpuID);

    pthread_mutex_unlock(&key);
}

void thread2 () {
    pthread_mutex_lock(&key);

    pid_t pid, tid;
    int cpuID;
    long cpuNo;
    cpu_set_t mask;

    pid = getpid();
    tid = syscall(SYS_gettid);
    cpuNo = sched_getcpu();
    printf("BlackHole: Thread-Y (PID: %d, TID: %d).\n", pid, tid);

    // showing which cpu is using
    cpuID = sched_getcpu();
    printf("[BlackHole-Y] At first, CPU ID: %d\n", cpuID);

    // showing no of cpu avaiable in the pc
    cpuNo = sysconf(_SC_NPROCESSORS_ONLN);
    printf("[BlackHole-Y] No. of available CPUS: %ld\n", cpuNo);

    // showing available cpu
    printf("[BlackHole-Y] Available CPUS are:\n");
    sched_getaffinity(0, sizeof(cpu_set_t), &mask);
    for (int i = 0; i < cpuNo; i++) {
        printf("%d ", CPU_ISSET(i, &mask));
    }
    printf("\n");

    CPU_ZERO(&mask);
    CPU_SET(3, &mask);
    sched_setaffinity(0, sizeof(cpu_set_t), &mask);

    //sched_getaffinity(0, sizeof(cpu_set_t), &mask);
    printf("[BlackHole-Y] After selecting CPU-2\n");
    printf("[BlackHole-Y] Now Available CPU is:\n");
    for (int i = 0; i < cpuNo; i++) {
        printf("%d ", CPU_ISSET(i, &mask));
    }
    printf("\n");

    cpuID = sched_getcpu();
    printf("[BlackHole-Y] Now CPU ID: %d\n", cpuID);

    pthread_mutex_lock(&key);
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
