#include <pthread.h>
#include <stdio.h>

int result;
int num[2];
pthread_mutex_t key;

void Ittu (void* arg) {
    pthread_mutex_lock(&key);
    int *x = arg;
    // printf("%d %d\n", x, y);

    printf("Before sum: %d\n", result);
    result = x[0] + x[1];
    printf("After sum: %d\n", result);

    pthread_mutex_unlock(&key);
}

void Bittu (int a, int b) {
    pthread_mutex_lock(&key);

    printf("Before sub: %d\n", result);
    result = a - b;
    printf("After sub: %d\n", result);

    pthread_mutex_unlock(&key);
}

void Mittu (int a, int b) {
    pthread_mutex_lock(&key);

    printf("Before mul: %d\n", result);
    result = a * b;
    printf("After mul: %d\n", result);

    pthread_mutex_unlock(&key);
}

int main(int argc, char const *argv[]) {
    int i, a, b;
    pthread_t tid1, tid2, tid3;


    scanf("%d %d", &num[0], &num[1]);
    printf("%d %d\n", num[0], num[1]);

    pthread_create(&tid1, NULL, (void *)Ittu, &num);
    // pthread_create(&tid1, NULL, Ittu(a, b), NULL);
    // pthread_create(&tid2, NULL, void(*)Bittu(a, b), NULL);
    // pthread_create(&tid3, NULL, Mittu(a, b), NULL);

    for (i = 0; i < 5; i++) {
        printf("Main thread, result: %d\n", result);
    }

    // pthread_join(tid1, NULL);
    pthread_join(tid2, NULL);
    // pthread_join(tid3, NULL);

    return 0;
}
