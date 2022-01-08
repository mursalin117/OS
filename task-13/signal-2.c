// SIGCONT
// SIGSTOP
// SIGTERM
// SIGKILL
// SIGHUP
// SIGUSER1
// SIGUSER2

#include <stdio.h>
#include <signal.h>
#include <unistd.h>

void signal_handler(int c) {
    printf("Hello, Signal is processed\n");
}

int main(int argc, char const *argv[]) {
    int i;
    pid_t pid;

    pid = getpid();

    signal(SIGTERM, signal_handler);

    for (i = 0; i < 10000000; i++) {
        printf("%d. PID: %u\n",i, pid);
        sleep(5);
    }
    return 0;
}
