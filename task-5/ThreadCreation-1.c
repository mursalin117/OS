#include <stdio.h>
#include <pthread.h>

void sum() {
   
   int i;
    
    for (i = 0; i < 50; i++) { 
    	printf("Sum Thread\n");
    }

}

int main() {
    
    int i;
    pthread_t threadID;
    
    pthread_create(&threadID, NULL, (void *) sum, NULL);
    // sum();
    
    for (i = 0; i < 50; i++) { 
    	printf("Main Thread\n");
    }
    return 0;
}
