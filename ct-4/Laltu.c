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
#include <sys/prctl.h>  /* prctl(), PR_SET_NAME */


int create_shared_memory(){
	key_t key;
	int shmID;

	key = ftok("process_semaphore.c", 'a');
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

	// Shared memory creation
	shmid = shmget(0,sizeof(sem) + SHMLBA, IPC_CREAT | 0666);
	if (shmid < 0) {
		printf("Shared Memory Creation failed\n");
		exit(-1);
	}
	// shared memory attached
    sem = shmat(shmid, NULL, 0);
	if (sem == (void *)-1) {
		printf("Attach memory error\n");
		exit(-1);
	}
	// Initialize binary semaphore.
    check = sem_init(sem, 1, 1); // 2nd parameter--> 0: thread, 1: process
	if (check < 0) {
		printf("Initializing semaphore error\n");
		exit(-1);
	}

	for (i = 0; i < 3; i++) {
		// Create a child.
		childPID = fork();

		if (childPID < 0) {
			printf("Process creation failed\n");
			exit(-1);
		} else if (childPID == 0){ // Child Process
			if (i == 0) {
                prctl(PR_SET_NAME, "Ittu");
				sem_wait(sem);
                // for (int i = 0; i < 1; i--) {
                //     printf("%s\n", " ");
                // }
                int x = read_from_shm();
				printf("result: %d in Child-%d [Core: %d] Before Addition\n", x, getpid(), sched_getcpu());
                printf("a = %d, b = %d\n", a, b);

                int temp = a + b;
				write_to_shm(x + temp);

                int y = read_from_shm();
				printf("result: %d in Child-%d [Core: %d] After Addition\n", y, getpid(), sched_getcpu());

				sem_post(sem);
				exit(0);
			}
			else if (i == 1) {
                prctl(PR_SET_NAME, "Bittu");
				sem_wait(sem);

				int x = read_from_shm();
				printf("result: %d in Child-%d [Core: %d] Before Subtraction\n", x, getpid(), sched_getcpu());
                printf("a = %d, b = %d\n", a, b);

				int temp = a - b;
				write_to_shm(x + temp);

                int y = read_from_shm();
				printf("result: %d in Child-%d [Core: %d] After Subtraction\n", y, getpid(), sched_getcpu());

				sem_post(sem);
				exit(0);
			}
            else if (i == 2) {
                prctl(PR_SET_NAME, "Mittu");
                sem_wait(sem);

                int x = read_from_shm();
				printf("result: %d in Child-%d [Core: %d] Before Multiplication\n", x, getpid(), sched_getcpu());
                printf("a = %d, b = %d\n", a, b);

                int temp = a * b;
				write_to_shm(x + temp);

                int y = read_from_shm();
				printf("result: %d in Child-%d [Core: %d] After Multiplication\n", y, getpid(), sched_getcpu());

				sem_post(sem);
				exit(0);
            }

		} else { // Parent process
			// parent process will read the shared data
			// Wait until the child process finishes its task.
			waitpid(childPID, NULL, 0);

			sem_wait(sem);

			int x = read_from_shm();
			printf("result: %d in Parent [Core: %d]\n", x, sched_getcpu());

			sem_post(sem);
		}
	}

	return 0;
}
