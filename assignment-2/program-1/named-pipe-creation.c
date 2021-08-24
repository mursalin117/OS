#include <stdio.h>
#include <sys/stat.h>
#include <unistd.h>
#include <stdlib.h>

int main(){
	char *pipePath;
	int pipeFlag, fd;

	// Create a named pipe
	pipePath = "./myPipe";
	if(access(pipePath, F_OK) == 0) { // Pipe exists
		printf("%s is already created, so new pipe will not be created\n. ", pipePath);
	} else {// Pipe does not exists, so we can create a new pipe.
		pipeFlag = mkfifo(pipePath, 0666); // mkfifo(pipePath, permission)
		if (pipeFlag < 0){
			printf("Error in creating a named pipe.\n");
			exit(-1);
		} else{
			printf("Pipe has been created successfully.\n");
		}
	}

	return 0;
}
