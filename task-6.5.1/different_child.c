#define _GNU_SOURCE

#include <pthread.h>
#include <stdio.h>
#include <sys/types.h>
#include <unistd.h>
#include <sys/syscall.h>
#include <sched.h>

void thread1 () {
    int i, cpuNo;
    pid_t pid, tid;

    for (i = 0; i < 10; i++) {
        pid = getpid();
        tid = syscall(SYS_gettid);
        cpuNo = sched_getcpu();
        printf("Sub-thread 1 (PID: %d, TID: %d CPU: %d).\n", pid, tid, cpuNo);
    }
}

void thread2 () {
    int i, cpuNo;
    pid_t pid, tid;

    for (i = 0; i < 10; i++) {
        pid = getpid();
        tid = syscall(SYS_gettid);
        cpuNo = sched_getcpu();
        printf("Sub-thread 2 (PID: %d, TID: %d CPU: %d).\n", pid, tid, cpuNo);
    }
}

int main(int argc, char const *argv[]) {
    pid_t pid, tid, childPID;
    pthread_t tid1, tid2;
    int i, cpuNo;

    childPID = fork();

    if (childPID == 0) { // child process
        // creating two thread
        pthread_create(&tid1, NULL, (void*) thread1, NULL);
        pthread_create(&tid2, NULL, (void*) thread2, NULL);

        // task done by main thread
        for (i = 0; i < 10; i++) {
            pid = getpid();
            tid = gettid();//syscall(SYS_gettid);
            cpuNo = sched_getcpu();
            printf("Main thread (PID: %d, TID: %d CPU: %d).\n", pid, tid, cpuNo);
        }

        // wait until finishing task
        pthread_join(tid1, NULL);
        pthread_join(tid2, NULL);
    } else if (childPID > 0) { // parent process
        // creating two thread
        pthread_create(&tid1, NULL, (void*) thread1, NULL);
        pthread_create(&tid2, NULL, (void*) thread2, NULL);

        // task done by main thread
        for (i = 0; i < 10; i++) {
            pid = getpid();
            tid = gettid();//syscall(SYS_gettid);
            cpuNo = sched_getcpu();
            printf("Main thread (PID: %d, TID: %d CPU: %d).\n", pid, tid, cpuNo);
        }

        // wait until finishing task
        pthread_join(tid1, NULL);
        pthread_join(tid2, NULL);
    }

    return 0;
}
