/*
    here the nammed semaphore is used
*/

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

int main(){
    sem_t *sem1,*sem2;
    pid_t childPID;
    int a, b, x;

    // Put shareable data into shared memory so that both parent and child can perform operation on it.
    x = 10; // Shared data
    write_to_shm(x);

    // named semaphore is created using sem_open
    sem1 = sem_open("/firstSem", O_CREAT, 0644, 1);
    sem2 = sem_open("/secondSem", O_CREAT, 0644, 1);
    // Create a child.
    childPID = fork();

    // Child process will increase value of shared data & parent process will decrease value of shared data.
    if (childPID == 0){ // Child Process
        sem_wait(sem1);

        a = read_from_shm();
        printf("x: %d in Child [Core: %d] Before Addition\n", a, sched_getcpu());
        a = a + 1;
        write_to_shm(a);
        b = read_from_shm();
        printf("x: %d in Child [Core: %d] After Addition\n", b, sched_getcpu());

        sem_post(sem2);

    }else{ // Parent process

        sem_wait(sem2);

        a = read_from_shm();
        printf("x: %d in Parent [Core: %d] Before Subtraction\n", a, sched_getcpu());
        a = a - 1;
        write_to_shm(a);
        b = read_from_shm();
        printf("x: %d in Parent [Core: %d] After Subtraction\n", b, sched_getcpu());

        sem_post(sem1);

        // Wait until the child process finishes its task.
        waitpid(childPID,NULL,0);
    }

    return 0;
}
