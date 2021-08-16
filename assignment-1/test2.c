#include <stdio.h>
#include <unistd.h>

int main(int argc, char const *argv[]) {
    execlp("./sum", "sum", "rafi", "mamun", "shahriar", "mursalin", NULL);
    return 0;
}
