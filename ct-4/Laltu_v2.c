#define _GNU_SOURCE
#include <sys/ipc.h>
#include <stdio.h>
#include <sys/shm.h>
#include <string.h>
#include <sched.h>
#include <unistd.h>
#include <stdlib.h>
#include <semaphore.h>
#include <sys/wait.h>
#include <fcntl.h>

int create_shared_memory(){
    key_t key;
    int shmID;

    key = ftok("threadSemaphore.c", 'a');
    shmID = shmget(key, 1024, IPC_CREAT | 0666);

    return shmID;
}

void write_to_shm(int x){
    int shmID = create_shared_memory();

    // Attach shared memory with the ddress space of the process.
    char *str = shmat(shmID, NULL, 0);

    // Convert integer into a string.
    char num[100];
    sprintf(num, "%d", x);

    // Put integer data into the shared memory.
    strcpy(str, num);

    // Detach the shared memory segment.
    shmdt(str);
}

int read_from_shm(){
    int shmID = create_shared_memory();

    // Attach shared memory with the address space of the process.
    char *str = shmat(shmID, NULL, 0);

    // Convert string to integer
    int num = (int) strtol(str, (char **)NULL, 10);

    // Detach the shared memory segment.
    shmdt(str);

    return num;
}

int main(){
	sem_t * sem;
	pid_t childPID;
	int a, b, result, shmid, i, check;

    scanf("%d%d", &a, &b);

	// Put shareable data into shared memory so that both parent and child can perform operation on it.
	result = 0; // Shared data
	write_to_shm(result);

    // named semaphore is created using sem_open
    sem = sem_open("/firstSem", O_CREAT, 0666, 1);
    if (sem == SEM_FAILED) {
        printf("Semaphore error\n");
        exit(-1);
    }

	for (i = 0; i < 3; i++) {
		// Create a child.
		childPID = fork();

		if (childPID < 0) {
			printf("Process creation failed\n");
			exit(-1);
		} else if (childPID == 0){ // Child Process
            char num1[100], num2[100];
            sprintf(num1, "%d", a);
            sprintf(num2, "%d", b);
			if (i == 0) {
                execlp("./Ittu", num1, num2, NULL);
			}
			else if (i == 1) {
				execlp("./Bittu", num1, num2, NULL);
			}
            else if (i == 2) {
                execlp("./Mittu", num1, num2, NULL);
            }

		} else { // Parent process
			// parent process will read the shared data
			// Wait until the child process finishes its task.
			waitpid(childPID, NULL, 0);

			sem_wait(sem);

			int x = read_from_shm();
			printf("Result: %d in Parent [Core: %d]\n", x, sched_getcpu());

			sem_post(sem);

		}
	}

	return 0;
}
