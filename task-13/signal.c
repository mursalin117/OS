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

int main(int argc, char const *argv[]) {
    int i;
    pid_t pid;

    pid = getpid();

    for (i = 0; i < 10000000; i++) {
        printf("%d. PID: %u\n",i, pid);
        sleep(5);
    }
    return 0;
}
