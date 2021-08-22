// This is orphanage child process
// For not creating orphanage process use wait()

#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/wait.h>

int main(int argc, char const *argv[]) {
    pid_t cpid, pid;
    int i;

    cpid = fork();
    if (cpid < 0) { // negative value for failure
        printf("Child process creating unsuccessful\n");
        exit(-1); // turn off execution
    }
    else if (cpid == 0) { // '0' for child process and start child process
        for (i = 0; i < 1; i--) {
            pid = getpid();
            printf("This is child process %u\n", pid);
        }
    }
    else if (cpid > 0) { // > 0 for parent process and start parent process
        //for (i = 0; i < 1; i--) {
            int *wstatus;
            pid_t status;
            pid = getpid();
            printf("This is parent process %u and child process is %u\n", pid, cpid);
            status = wait(wstatus);
            printf("Child status = %u\n", status);
        //}
    }

    return 0;
}
