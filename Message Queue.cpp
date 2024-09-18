#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/msg.h>
#include <string.h>

#define MAX_MESSAGE_SIZE 100

// Message structure
struct Message {
    long messageType;
    char messageText[MAX_MESSAGE_SIZE];
};

int main() {
    key_t key;
    int messageQueueID;

    // Generate a unique key for the message queue
    if ((key = ftok("message_queue_example", 'B')) == -1) {
        perror("ftok");
        exit(EXIT_FAILURE);
    }

    // Create a message queue (or get the ID of an existing one)
    if ((messageQueueID = msgget(key, 0644 | IPC_CREAT)) == -1) {
        perror("msgget");
        exit(EXIT_FAILURE);
    }

    // Sender process
    struct Message message;
    message.messageType = 1; // Message type (can be any positive integer)

    printf("Sender: Enter a message to send: ");
    fgets(message.messageText, MAX_MESSAGE_SIZE, stdin);

    // Send the message to the message queue
    if (msgsnd(messageQueueID, &message, sizeof(message.messageText), 0) == -1) {
        perror("msgsnd");
        exit(EXIT_FAILURE);
    }

    printf("Sender: Message sent to the message queue.\n");

    // Receiver process
    // Receive the message from the message queue
    if (msgrcv(messageQueueID, &message, sizeof(message.messageText), 1, 0) == -1) {
        perror("msgrcv");
        exit(EXIT_FAILURE);
    }

    printf("Receiver: Received message: %s", message.messageText);

    // Remove the message queue
    if (msgctl(messageQueueID, IPC_RMID, NULL) == -1) {
        perror("msgctl");
        exit(EXIT_FAILURE);
    }

    return 0;
}

