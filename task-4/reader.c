// reader for the pipe

#include <unistd.h>
#include <fcntl.h>
#include <string.h>
#include <stdio.h>

int main(int argc, char const *argv[]) {
    int fd;
    char *pipePath;
    char buffer[200];

    // pipe path
    pipePath = "./myPipe";

    // file descriptor
    fd = open(pipePath, O_RDONLY);

    // reading from pipe
    read(fd, buffer, sizeof(buffer));

    // closing file descriptor
    close(fd);

    // showing what is got by reader
    // printf("writer says: %s\n", buffer);
    write(STDOUT_FILENO, buffer, strlen(buffer));

    return 0;
}
