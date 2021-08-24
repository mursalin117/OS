#include <stdio.h>
#include <sys/stat.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>

int main(){

	int pipeFlag, fd, i;

    for (i = 1; i < 4; i++) {
        // Create a named pipe
        char pipePath[200] = "./myPipe";
        int length = snprintf( NULL, 0, "%d", i );
        char* n = malloc( length + 1 );
        snprintf( n, length + 1, "%d", i );

        strcat(pipePath, n);
        // printf("%s\n", pipePath);

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
    }

	return 0;
}
