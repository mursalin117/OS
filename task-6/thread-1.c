#include <pthread.h>
#include <stdio.h>

int x = 100;

void sum () {
    printf("Before sum: %d\n", x);
    x = x + 1;
    printf("After sum: %d\n", x);
}

void sub () {
    printf("Before sub: %d\n", x);
    x = x - 1;
    printf("After sub: %d\n", x);
}

int main(int argc, char const *argv[]) {
    int i;
    pthread_t tid1, tid2;

    pthread_create(&tid1, NULL, (void *) sum, NULL);
    pthread_create(&tid2, NULL, (void *) sub, NULL);

    for (i = 0; i < 5; i++) {
        printf("Main thread, x: %d\n", x);
    }

    return 0;
}
