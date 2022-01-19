#define _GNU_SOURCE
#include <pthread.h>
#include <stdio.h>
#include <unistd.h>
#include <sys/syscall.h>
#include <signal.h>

int result;
pthread_mutex_t key;

void signal_handler(int c) {
    printf("Signal is got from child\n");
    kill(getpid(), SIGTERM);
}

void Ittu (void* arg) {
    pthread_mutex_lock(&key);
    int *x = arg;
    int cpuNo;
    pid_t pid, tid;

    printf("Before sum: %d\n", result);
    result = x[0] + x[1];
    printf("After sum: %d\n", result);

    pid = getpid();
    tid = syscall(SYS_gettid);
    cpuNo = sched_getcpu();
    printf("Ittu (PID: %d, TID: %d CPU: %d).\n", pid, tid, cpuNo);

    if (result == 100) {
        pthread_kill(pthread_self(), SIGUSR1);
    }

    pthread_mutex_unlock(&key);
}

void Bittu (void* arg) {
    pthread_mutex_lock(&key);
    int *x = arg;
    int cpuNo;
    pid_t pid, tid;

    printf("Before sub: %d\n", result);
    result = x[0] - x[1];
    printf("After sub: %d\n", result);

    pid = getpid();
    tid = syscall(SYS_gettid);
    cpuNo = sched_getcpu();
    printf("Bittu (PID: %d, TID: %d CPU: %d).\n", pid, tid, cpuNo);

    if (result == 100) {
        pthread_kill(pthread_self(), SIGUSR1);
    }

    pthread_mutex_unlock(&key);
}

void Mittu (void* arg) {
    pthread_mutex_lock(&key);
    int *x = arg;
    int cpuNo;
    pid_t pid, tid;

    printf("Before mul: %d\n", result);
    result = x[0] * x[1];
    printf("After mul: %d\n", result);

    pid = getpid();
    tid = syscall(SYS_gettid);
    cpuNo = sched_getcpu();
    printf("Mittu (PID: %d, TID: %d CPU: %d).\n", pid, tid, cpuNo);

    if (result == 100) {
        pthread_kill(pthread_self(), SIGUSR1);
    }

    pthread_mutex_unlock(&key);
}

int main(int argc, char const *argv[]) {
    int i, a, b;
    int num[2];
    pthread_t tid1, tid2, tid3;

    scanf("%d %d", &num[0], &num[1]);
    printf("%d %d\n", num[0], num[1]);

    for (i = 0; i < 10; i++) {
        signal(SIGUSR1, signal_handler);

        pthread_create(&tid1, NULL, (void *)Ittu, (void *)num);
        pthread_create(&tid2, NULL, (void *)Bittu, (void *)num);
        pthread_create(&tid3, NULL, (void *)Mittu, (void *)num);
    }

    pthread_join(tid1, NULL);
    pthread_join(tid2, NULL);
    pthread_join(tid3, NULL);

    return 0;
}
