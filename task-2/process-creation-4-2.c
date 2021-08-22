#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/wait.h>

int main(int argc, char const *argv[]) {
    pid_t status, pid;

    status = fork();

    if (status < 0) {
        printf("Process creation unsuccessful\n");
        exit(-1);
    }
    else if (status == 0) {
        printf("This is child process\n");
        printf("This is child process\n");
        printf("This is child process\n");
        printf("This is child process\n");
        printf("This is child process\n");
        printf("This is child process\n");
        printf("This is child process\n");
        printf("This is child process\n");
        printf("This is child process\n");
        printf("This is child process\n");
    }
    else if (status > 0) {
        //int *wstatus;
        printf("This is parent process\n");
        printf("This is parent process\n");
        printf("This is parent process\n");
        pid = getpid();
        printf("This is parent process - %u\n", pid);
        printf("This is parent process - %u\n", pid);
        printf("This is parent process - %u\n", pid);
        printf("This is parent process - %u\n", pid);
        printf("This is parent process - %u\n", pid);
        printf("This is parent process - %u\n", pid);
        //wait(wstatus);
    }

    return 0;
}
