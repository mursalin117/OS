#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <sys/wait.h>

int main(int argc, char *argv[]) {
    pid_t pid;
    int a, b, i;

    scanf("%d%d", &a, &b);

    int length1 = snprintf( NULL, 0, "%d", a );
    char* n1 = malloc( length1 + 1 );
    snprintf( n1, length1 + 1, "%d", a );

    int length2 = snprintf( NULL, 0, "%d", b );
    char* n2 = malloc( length2 + 1 );
    snprintf( n2, length2 + 1, "%d", b );

    for (i = 0; i < 4; i++) {
        pid = fork();
        if (pid < 0) {
            printf("Child Process is not created\n");
            exit(-1);
        }
        else if (pid == 0) {
            if (i == 0) {
                execlp("./sum", "sum", n1, n2, NULL);
            }
            else if (i == 1) {
                execlp("./sub", "sub", n1, n2, NULL);
            }
            else if (i == 2) {
                execlp("./mul", "mul", n1, n2, NULL);
            }
            else {
                execlp("./div", "div", n1, n2, NULL);
            }
        }
        else if (pid > 0) {
            wait(NULL);
        }
    }

    return 0;
}
