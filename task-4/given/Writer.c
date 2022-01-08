// 17.8.2021
// To write to a named pipe.

#include <unistd.h>
#include <fcntl.h>
#include <string.h>

int main(){
	int fd;
	char *pipePath;
	char *msg;

	pipePath = "/home/cse/OperatingSystem/ClassCode/1stPipe";
	msg = "Hello\n";
	fd = open(pipePath, O_WRONLY);	
	write(fd, msg, strlen(msg) + 1);
	close(fd);

	return 0;
}


