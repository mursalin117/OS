// 17.8.2021
// To read from a named pipe.

#include <unistd.h>
#include <fcntl.h>
#include <string.h>

int main(){
	int fd;
	char *pipePath;
	char buffer[200];

	pipePath = "/home/cse/OperatingSystem/ClassCode/1stPipe";
	fd = open(pipePath, O_RDONLY);	
	read(fd, buffer, sizeof(buffer));
	close(fd);

	// Display to the monitor.
	write(STDOUT_FILENO, buffer, strlen(buffer));

	return 0;
}
