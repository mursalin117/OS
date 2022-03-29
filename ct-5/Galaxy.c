#define  _GNU_SOURCE
#include <sched.h>
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/wait.h>
#include <sys/types.h>

int main(int argc, char const *argv[]) {
    pid_t childPID;
    int cpuID;
    long cpuNo;
    cpu_set_t mask;
    int policy;

    for (int i = 0; i < 2; i++) {
		// Create a child.
		childPID = fork();

		if (childPID < 0) {
			printf("Process creation failed\n");
			exit(-1);
		} else if (childPID == 0){ // Child Process
			if (i == 0) {
                for (int j = 0; j < 100; j++) {
                    execlp("./Nebula", " ", NULL);
                }
			}
			else if (i == 1) {
                for (int j = 0; j < 100; j++) {
                    execlp("./BlackHole", " ", NULL);
                }
			}

		} else { // Parent process
			// parent process will read the shared data
			// Wait until the child process finishes its task.
			waitpid(childPID, NULL, 0);

            for (int j = 0; j < 10; j++) {
                // showing the PID no
                printf("Galaxy-%d ", getpid());

                // showing which cpu is using
                cpuID = sched_getcpu();
                printf("CPU ID: %d\n", cpuID);

                // showing no of cpu avaiable in the pc
                cpuNo = sysconf(_SC_NPROCESSORS_ONLN);
                printf("No. available of CPUS: %ld\n", cpuNo);

                // showing available cpu
                printf("Available CPUS are:\n");
                sched_getaffinity(0, sizeof(cpu_set_t), &mask);
                for (int k = 0; k < cpuNo; k++) {
                    printf("%d ", CPU_ISSET(i, &mask));
                }
                printf("\n");

                // showing the scheduler
                policy = sched_getscheduler(0);
                printf("Scheduling Policy: %d\n", policy);
                printf("SCHED_OTHER = %d, SCHED_BATCH = %d, SCHED_IDLE = %d, SCHED_FIFO = %d, SCHED_RR = %d\n", SCHED_OTHER, SCHED_BATCH, SCHED_IDLE, SCHED_FIFO, SCHED_RR);
            }
        }
	}

    return 0;
}
