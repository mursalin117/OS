#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>

void lockScreen () {
    int err;
    if ((err = system("killall myTask"))){
        printf("There was an error (%i)\n", err);
    }
}

void shutdown () {
    int err;
    if ((err = system("shutdown -c"))){
        printf("There was an error (%i)\n", err);
    }
}

int main(int argc, char const *argv[]) {
    pid_t childPID;

    childPID = fork();

    if (childPID < 0) {
        printf("Process creation unsuccessful\n");
        exit(-1);
    }
    else if (childPID == 0) {
        if (strcmp(argv[1], "Poweroff-c") == 0) {
            shutdown();
        }
        else if (strcmp(argv[1], "lock-c") == 0){
            lockScreen();
        }
    }
    else {
        waitpid(childPID, NULL, 0);
    }

    return 0;
}
