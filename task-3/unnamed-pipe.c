#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/wait.h>

int main(int argc, char const *argv[]) {
    // file descriptor, pipeFD[0]: read purpose & pipeFD[1]: write purpose
    int pipeFD[2], status;
    pid_t childPID;

    // creat pipe
    status = pipe(pipeFD);
    if (status == -1) {
        printf("Pipe creation error!!!\n");
        exit(-1);
    }
    // printf("%d\n", status);

    childPID = fork();
    if (childPID < 0) {
        printf("Process creation unsuccessful\n");
        exit(-1);
    }
    else if (childPID == 0) { // child process
        printf("Child process is writing to pipe.\n");
        close(pipeFD[0]);
        char *msg = "Hello form child";
        write(pipeFD[1], msg, strlen(msg) + 1);
    }
    else if (childPID > 0) { // parent process
        wait(NULL);
        printf("Parent process is reading to pipe.\n");
        close(pipeFD[1]);
        char buffer[200];
        read(pipeFD[0], buffer, sizeof(buffer));
        printf("%s\n", buffer);
    }
    return 0;
}
