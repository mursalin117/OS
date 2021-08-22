#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/wait.h>

int main(int argc, char const *argv[]) {
    pid_t status, pid;
    int *wstatus;

    status = fork();

    if (status < 0) {
        printf("Process creation unsuccessful\n");
        exit(-1);
    }
    else if (status == 0) {
        execlp("/media/mursalin/New Volume/OS/task-2/hi", "Hi", NULL);
    }
    else if (status > 0) {
        pid = getpid();
        printf("This is parent process %u\n", pid);
        wait(wstatus);
    }
    return 0;
}
