// 17.8.2021
// To write to a named pipe.

#include <unistd.h>
#include <fcntl.h>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>

int main(){
	int fd, i;
	char *pipePath;


	pipePath = "./myPipe";

    for (i = 0; i < 1; i--) {
        char msg[200];
        fd = open(pipePath, O_WRONLY);
        if (fd < 0) {
            printf("File descriptor is not created\n");
            exit(-1);
        }
        scanf("%s", msg);
        write(fd, msg, strlen(msg) + 1);
    	//close(fd);
        if (!strcmp(msg, "-999")) {
            exit(0);
        }
    }

	return 0;
}
