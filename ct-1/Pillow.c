#define  _GNU_SOURCE
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <sched.h>

int main(int argc, char const *argv[]) {
    pid_t cpid1, cpid2, pid;
    int cpuID;
    int i;

    for (i = 0; i < 1; i--) {
        pid = getpid();
        cpuID = sched_getcpu();
        printf("I am child1 %u running at CPU-%d\n", pid, cpuID);
    }

    return 0;
}
