#include <stdio.h>

// argc gets how many parameter is given (the number)
//

int main(int argc, char const *argv[]) { // int main(int argc, char const **argv)
    int i;

    printf("Number of arguments: %d\n", argc);
    for (i = 0; i < argc; i++) {
        printf("Argument no %d: %s\n", i, argv[i]);
    }

    return 0;
}
