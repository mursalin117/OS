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
#include<fcntl.h>

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

int main(int argc, char *argv[]){
    sem_t * sem;

    //sem_t *sem = *(int)argv[3];
    int a = atoi(argv[0]);
    int b = atoi(argv[1]);

	pid_t pid;
	// int a, b, result, shmid, i, check;

    // named semaphore is created using sem_open
    sem = sem_open("/firstSem", O_CREAT, 0666, 1);
    if (sem == SEM_FAILED) {
        printf("Semaphore error\n");
        exit(-1);
    }

    sem_wait(sem);

    int x = read_from_shm();
    printf("Before Addition result: %d in Child-%d [Core: %d]\n", x, getpid(), sched_getcpu());
    printf("a = %d, b = %d\n", a, b);

    int temp = a + b;
    write_to_shm(x + temp);

    int y = read_from_shm();
    printf("After Addition result: %d in Child-%d [Core: %d]\n", y, getpid(), sched_getcpu());

    sem_post(sem);

    return 0;
}
