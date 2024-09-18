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

    // Exit the main thread
    pthread_exit(NULL);

    // This line will not be reached
    printf("This line will not be executed\n");

    return 0;
}

