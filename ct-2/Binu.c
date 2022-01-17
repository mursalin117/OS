// reader for the pipe

#include <unistd.h>
#include <fcntl.h>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>

int main(int argc, char const *argv[]) {
    int fd, i;
    char buffer[200];


    for (i = 0; i < 1; i--) {
        char buffer[200];
        fd = open(argv[1], O_RDONLY);
        if (fd < 0) {
            printf("File descriptor is not created\n");
            exit(-1);
        }
        read(fd, buffer, sizeof(buffer));
    	//close(fd);

        // Display to the monitor.
    	// write(STDOUT_FILENO, buffer, strlen(buffer));
        printf("%s\n", buffer);

        if (!strcmp(buffer, "Bye")) {
            exit(0);
        }

    }

    // file descriptor
    // fd = open(argv[1], O_RDONLY);
    //
    // // reading from pipe
    // read(fd, buffer, sizeof(buffer));
    //
    // // closing file descriptor
    // close(fd);
    //
    // // showing what is got by reader
    // // printf("writer says: %s\n", buffer);
    // write(STDOUT_FILENO, buffer, strlen(buffer));

    return 0;
}
