// parent and child process is created and contineously running
// check using top, pstree -pas, pstree -ps command

#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>

int main() {
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
        for (i = 0; i < 1; i--) {
            pid = getpid();
            printf("This is parent process %u and child process is %u\n", pid, cpid);
        }
    }

    return 0;
}
