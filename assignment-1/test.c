#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>

int main(int argc, char const *argv[]) {
    int a, b, status;

    scanf("%d %d", &a, &b);

    int length1 = snprintf( NULL, 0, "%d", a );
    char* n1 = malloc( length1 + 1 );
    snprintf( n1, length1 + 1, "%d", a );

    int length2 = snprintf( NULL, 0, "%d", b );
    char* n2 = malloc( length2 + 1 );
    snprintf( n2, length2 + 1, "%d", b );

    status = execlp("./sum", "sum", n1, n2, NULL);
    // status = system("./sum");

    return 0;
}
