// writer for the pipe

#include <unistd.h>
#include <fcntl.h>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>

int main(int argc, char const *argv[]) {
    int fd, i;
    char str[200];
    pid_t pid, ppid;

    pid = getpid();
    ppid = getppid();

    int length1 = snprintf( NULL, 0, "%d", pid );
    char* n1 = malloc( length1 + 1 );
    snprintf( n1, length1 + 1, "%d", pid );

    strcat(str, "My PID no is ");
    strcat(str, n1);

    int length2 = snprintf( NULL, 0, "%d", ppid );
    char* n2 = malloc( length2 + 1 );
    snprintf( n2, length2 + 1, "%d", ppid );

    strcat(str, " My Parent's PID no is ");
    strcat(str, n2);

    strcat(str, "\nHello");

    fd = open(argv[1], O_WRONLY);
    if (fd < 0) {
        printf("File descriptor is not created\n");
        exit(-1);
    }
    write(fd, str, strlen(str) + 1);

    for (i = 0; i < 1; i--) {
        char msg[200];
        fd = open(argv[1], O_WRONLY);
        if (fd < 0) {
            printf("File descriptor is not created\n");
            exit(-1);
        }
        scanf("%s", msg);
        write(fd, msg, strlen(msg) + 1);
    	//close(fd);
        if (!strcmp(msg, "Bye")) {
            exit(0);
        }
    }

    // message
    // msg = "hello\n";
    //
    // // file descriptor
    // fd = open(argv[1], O_WRONLY);
    //
    // // writing on pipe
    // write(fd, msg, strlen(msg));

    // closing file descriptor
    close(fd);

    return 0;
}
