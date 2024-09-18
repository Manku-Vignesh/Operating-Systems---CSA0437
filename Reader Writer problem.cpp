#include <stdio.h>
#include <pthread.h>
#include <semaphore.h>
#include <unistd.h>

#define MAX_READERS 5
#define MAX_WRITERS 5

// Shared resource (e.g., database)
int sharedResource = 0;

// Semaphores
sem_t mutex;          // Controls access to the shared resource
sem_t readerMutex;    // Controls access to the reader count
sem_t writerMutex;    // Controls access to the writer count

int readerCount = 0;  // Number of readers currently accessing the resource

// Reader function
void *reader(void *arg) {
    int readerID = *((int *)arg);

    while (1) {
        // Entry section
        sem_wait(&readerMutex);
        readerCount++;
        if (readerCount == 1) {
            sem_wait(&mutex);  // First reader acquires the resource lock
        }
        sem_post(&readerMutex);

        // Critical section
        printf("Reader %d is reading: %d\n", readerID, sharedResource);
        sleep(1); // Simulate reading

        // Exit section
        sem_wait(&readerMutex);
        readerCount--;
        if (readerCount == 0) {
            sem_post(&mutex);  // Last reader releases the resource lock
        }
        sem_post(&readerMutex);

        // Non-critical section
        sleep(2); // Simulate other activities
    }

    pthread_exit(NULL);
}

// Writer function
void *writer(void *arg) {
    int writerID = *((int *)arg);

    while (1) {
        // Entry section
        sem_wait(&writerMutex);
        sem_wait(&mutex);  // Writer acquires the resource lock
        sem_post(&writerMutex);

        // Critical section
        sharedResource++;
        printf("Writer %d is writing: %d\n", writerID, sharedResource);
        sleep(1); // Simulate writing

        // Exit section
        sem_post(&mutex);  // Writer releases the resource lock

        // Non-critical section
        sleep(3); // Simulate other activities
    }

    pthread_exit(NULL);
}

int main() {
    // Initialize semaphores
    sem_init(&mutex, 0, 1);
    sem_init(&readerMutex, 0, 1);
    sem_init(&writerMutex, 0, 1);

    // Create reader threads
    pthread_t readerThreads[MAX_READERS];
    int readerIDs[MAX_READERS];
    for (int i = 0; i < MAX_READERS; i++) {
        readerIDs[i] = i + 1;
        pthread_create(&readerThreads[i], NULL, reader, (void *)&readerIDs[i]);
    }

    // Create writer threads
    pthread_t writerThreads[MAX_WRITERS];
    int writerIDs[MAX_WRITERS];
    for (int i = 0; i < MAX_WRITERS; i++) {
        writerIDs[i] = i + 1;
        pthread_create(&writerThreads[i], NULL, writer, (void *)&writerIDs[i]);
    }

    // Join threads
    for (int i = 0; i < MAX_READERS; i++) {
        pthread_join(readerThreads[i], NULL);
    }
    for (int i = 0; i < MAX_WRITERS; i++) {
        pthread_join(writerThreads[i], NULL);
    }

    // Destroy semaphores
    sem_destroy(&mutex);
    sem_destroy(&readerMutex);
    sem_destroy(&writerMutex);

    return 0;
}

