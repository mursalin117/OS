#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>

int main(int argc, char const *argv[]) {
    int num1, num2, fd0, fd1, result;

    fd0 = atoi(argv[1]);
    fd1 = atoi(argv[2]);
    
    num1 = atoi(argv[3]);
    num2 = atoi(argv[4]);

    close(fd0);

    result = num1 + num2;
    printf("Result = %d\n", result);

    char str[200] = "The sum is ";
    printf("%s\n", str);

    int length = snprintf( NULL, 0, "%d", result );
    char* strNum = malloc( length + 1 );
    snprintf( strNum, length + 1, "%d", result );

    printf("Result as string %s\n", strNum);

    strcat(str, strNum);

    printf("The sending string: %s\n", str);

    write(fd1, str, strlen(str) + 1);

    // close(pipeFD[1]);

    printf("After send\n");

    printf("inside sum : %u\n", getpid());
    exit(0);

    return 0;
}
