// named pipe creation

/*
    permission: read(R), write(W), execution(x)
                        user    group   others
    read(r): 100            4       4       4
    write(w): 010           2       2       2
    execution(x): 001       1       1       1
    ----------------------------------------------
    All excess        0     7       7       7

                        user    group   others
    read(r): 100            4       4       4
    write(w): 010           2       2       0
    execution(x): 001       0       0       0
    ----------------------------------------------
    read and write     0    6       6       4
*/

#include <stdio.h>
#include <sys/stat.h>
#include <unistd.h>
#include <stdlib.h>

int main(int argc, char const *argv[]) {
    char *pipePath;
    int pipeFlag;
    int fd;

    // creating a named pipe
    pipePath = "./myPipe";
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
    return 0;
}
