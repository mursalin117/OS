#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>

int main(int argc, char const *argv[]) {
    int num1, num2;

    num1 = atoi(argv[1]);
    num2 = atoi(argv[2]);

    printf("The div is %.2f\n", (float)num1 / (float)num2);
    return 0;
}
