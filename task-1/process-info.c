// checking the process id of the running program and
// checking command 'ps', 'pstree -ps', 'pstree -pas'

#include <unistd.h>
#include <stdio.h>

int main() {
    pid_t cpid, ppid;
    int i;
    // get child pid
    cpid = getpid();
    // get parent pid
    ppid = getppid();

    for (i = 0; i < 1; i--) {
        printf("Chid pid is %u\n", cpid);
        printf("Parent pid is %u\n", ppid);
    }

    return 0;
}
