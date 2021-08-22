// Here child process will run another code

#include<unistd.h>
#include<stdio.h>
#include<sys/wait.h>
#include<stdlib.h>

int main(){
	pid_t childPID, pid, deadChildPID;

	childPID = fork();

	if (childPID == -1){
		printf("Child process has not been created.\n");
		exit(-1);
	}
	else if (childPID == 0){
		execlp("/media/mursalin/New Volume/OS/task-1/child-process", "Child-Process", NULL); // Different code for child process.
		//execlp(Path_of_Exefile, Name_of_ChildProcess, NULL)
	}
	else if (childPID > 1){
		pid = getpid();
		printf("I am parent-%u. My child process-%u\n", pid, childPID);
		deadChildPID = wait(NULL); // Parent process will wait for the termination of the child process.
		printf("Dead child-%u.\n", deadChildPID);
	}

	return 0;
}
