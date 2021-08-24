// 17.8.2021
// To write to a named pipe.

#include <unistd.h>
#include <fcntl.h>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>

int main(){
	int fd, i;
	char *pipePath1, *pipePath2;


	pipePath1 = "./myPipe3";

    char msg[200];
    fd = open(pipePath1, O_WRONLY);
    if (fd < 0) {
        printf("File descriptor is not created\n");
        exit(-1);
    }
    scanf("%s", msg);
    write(fd, msg, strlen(msg) + 1);
    //close(fd);

    pipePath2 = "./myPipe2";
    char buffer[200];
    fd = open(pipePath2, O_RDONLY);
    if (fd < 0) {
        printf("File descriptor is not created\n");
        exit(-1);
    }
    read(fd, buffer, sizeof(buffer));
    //close(fd);

    // Display to the monitor.
    // write(STDOUT_FILENO, buffer, strlen(buffer));
    printf("%s\n", buffer);

	return 0;
}
