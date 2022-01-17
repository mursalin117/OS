#include <stdio.h>
#include <sys/stat.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>

int main(int argc, char *argv[]) {
    char *pipePath;
    int pipeFlag;
    int fd;

    // creating a named pipe
    for (int i = 1; i < argc; i++) {
        pipePath = argv[i];
        if (access(pipePath, F_OK) == 0) { // if pipe exists
            printf("Pipe is already exists.\n");
            printf("So, no pipe is created.\n");
        } else { // if pipe doesn't exist. So creating new pipe.
            // mkfifo(pipePath/name, permission);
            pipeFlag = mkfifo(pipePath, 0666);
            if (pipeFlag < 0) {
                printf("Error in creating new pipe.\n");
                exit(-1);
            } else {
                printf("Pipe is successfully created.\n");
            }
        }
    }

    return 0;
}
