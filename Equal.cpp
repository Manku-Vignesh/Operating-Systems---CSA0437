#include <stdio.h>
#include <pthread.h>

void *threadFunction(void *arg) {
    printf("Inside the new thread\n");
    pthread_exit(NULL);
}

int main() {
    pthread_t thread1, thread2;

    // Create two new threads
    if (pthread_create(&thread1, NULL, threadFunction, NULL) != 0 || 
        pthread_create(&thread2, NULL, threadFunction, NULL) != 0) {
        fprintf(stderr, "Error creating threads\n");
        return 1;
    }

    // Check if the two threads are equal
    if (pthread_equal(thread1, thread2)) {
        printf("Threads are equal\n");
    } else {
        printf("Threads are not equal\n");
    }

    // Wait for the created threads to finish
    if (pthread_join(thread1, NULL) != 0 || pthread_join(thread2, NULL) != 0) {
        fprintf(stderr, "Error joining threads\n");
        return 1;
    }

    return 0;
}

