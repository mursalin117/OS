// writer for the pipe

#include <unistd.h>
#include <fcntl.h>
#include <string.h>

int main(int argc, char const *argv[]) {
    int fd;
    char *pipePath;
    char *msg;

    // pipe path
    pipePath = "./myPipe";

    // message
    msg = "hello\n";

    // file descriptor
    fd = open(pipePath, O_WRONLY);

    // writing on pipe
    write(fd, msg, strlen(msg));

    // closing file descriptor
    close(fd);

    return 0;
}
