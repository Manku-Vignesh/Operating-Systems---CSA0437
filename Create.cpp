#include <stdio.h>
#include <pthread.h>

void *threadFunction(void *arg) {
    printf("Inside the new thread\n");
    pthread_exit(NULL);
}

int main() {
    pthread_t thread;

    // Create a new thread
    if (pthread_create(&thread, NULL, threadFunction, NULL) != 0) {
        fprintf(stderr, "Error creating thread\n");
        return 1;
    }

    printf("Inside the main thread\n");

    // Wait for the created thread to finish
    if (pthread_join(thread, NULL) != 0) {
        fprintf(stderr, "Error joining thread\n");
        return 1;
    }

    return 0;
}

