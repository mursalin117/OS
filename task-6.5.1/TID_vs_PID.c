#include <unistd.h>
#include <pthread.h>
#include <syscall.h>
#include <unistd.h>
#include <stdio.h>

void thread1() {
    pid_t pid, tid;

    pid = getpid();
    tid = syscall(SYS_gettid); // getgid();

    printf("Thread1: PID: %u, TID: %u\n", pid, tid);
}

void thread2() {
    pid_t pid, tid;

    pid = getpid();
    tid = syscall(SYS_gettid); // getgid();

    printf("Thread2: PID: %u, TID: %u\n", pid, tid);
}

int main(int argc, char const *argv[]) {
    pid_t pid, tid;
    pthread_t tid1, tid2;

    pthread_create(&tid1, NULL, (void *) thread1, NULL);
    pthread_create(&tid2, NULL, (void *) thread2, NULL);

    pid = getpid();
    tid = syscall(SYS_gettid); // getgid();
    printf("Main Thread: PID: %u, TID: %u\n", pid, tid);

    pthread_join(tid1, NULL);
    pthread_join(tid2, NULL);

    return 0;
}
