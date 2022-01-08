// strcpy()

#include <stdio.h>
#include <string.h>

void simple_copy_function(char *str);

int main(int argc, char *argv[]) {
    for (int i = 0; i < argc; i++) {
        printf("Argument %d is: %s\n",i, argv[i]);
        simple_copy_function(argv[i]);
    }

    printf("Every thing is fine.\n");

    return 0;
}

void simple_copy_function(char *str) {
    char buffer[5];
    int l = strlen(str);
    int m = sizeof(buffer);
    printf("%d, %d\n", l, m);

    if (strlen(str) < sizeof(buffer)) {
        strcpy(buffer, str);
        printf("Buffer: %s\n", buffer);
    }
}
