// 17.8.2021
// To read from a named pipe.

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
        char buffer[200];
        fd = open(pipePath, O_RDONLY);
        if (fd < 0) {
            printf("File descriptor is not created\n");
            exit(-1);
        }
        read(fd, buffer, sizeof(buffer));
    	//close(fd);

        if (!strcmp(buffer, "-999")) {
            exit(0);
        }

    	// Display to the monitor.
    	// write(STDOUT_FILENO, buffer, strlen(buffer));
        printf("%s\n", buffer);

    }


	return 0;
}
