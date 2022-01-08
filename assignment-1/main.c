#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <sys/wait.h>

int main(int argc, char *argv[]) {
    pid_t pid, ppid, cpid, mpid;
    int a, b, i;

    int pipeFD[2], status;
    if (status = pipe(pipeFD)) {
        printf("unsuccessful pipe creation\n");
    }

    scanf("%d%d", &a, &b);

    int length1 = snprintf( NULL, 0, "%d", a );
    char* n1 = malloc( length1 + 1 );
    snprintf( n1, length1 + 1, "%d", a );

    int length2 = snprintf( NULL, 0, "%d", b );
    char* n2 = malloc( length2 + 1 );
    snprintf( n2, length2 + 1, "%d", b );

    mpid = getpid();
    printf("Main process : %u\n", mpid);

    for (i = 0; i < 4; i++) {
        pid = fork();
        if (pid < 0) {
            printf("Child Process is not created\n");
            exit(-1);
        }
        else if (pid > 0) {
            printf("inside parent\n");
            int *d;
            // wait(NULL);
            close(pipeFD[1]);
            printf("Before getting text\n");
            char buffer[250];
		    read(pipeFD[0], buffer, sizeof(buffer));
            // close(pipeFD[0]);
            printf("Getting text from child\n");
            printf("%s\n", buffer);

            ppid = getpid();
            printf("Parent process : %u and child process : %u\n", ppid, pid);
            wait(NULL);
        }
        else if (pid == 0) {
            cpid = getpid();
            printf("Child process : %u\n", cpid);

            int len1 = snprintf( NULL, 0, "%d", pipeFD[0] );
            char* fd0 = malloc( len1 + 1 );
            snprintf( n1, len1 + 1, "%d", pipeFD[0] );

            int len2 = snprintf( NULL, 0, "%d", pipeFD[1] );
            char* fd1 = malloc( len2 + 1 );
            snprintf( n2, len2 + 1, "%d", pipeFD[1] );
            // exit(0);
            if (i == 0) {
                printf("inside child\n");
                execlp("./sum", "sum", fd0, fd1, n1, n2, NULL);
                // exit(0);
            }
            // else if (i == 1) {
            //     execlp("./sub", "sub", n1, n2, NULL);
            // }
            // else if (i == 2) {
            //     execlp("./mul", "mul", n1, n2, NULL);
            // }
            // else {
            //     execlp("./div", "div", n1, n2, NULL);
            // }
            cpid = getpid();
            printf("Child process : %u\n", cpid);
            // exit(0);
        }
    }

    return 0;
}
