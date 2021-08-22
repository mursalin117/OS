// This code is for child process

#include<stdio.h>
#include<unistd.h>

int main(){
	pid_t pid;

	pid = getpid();
	printf("I am child-%u.\n", pid);

	return 0;
}
