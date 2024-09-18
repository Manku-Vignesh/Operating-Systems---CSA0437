#include <stdio.h>
#include <stdlib.h>

void sort(int arr[], int n) {
    int i, j, temp;
    for (i = 0; i < n - 1; i++) {
        for (j = 0; j < n - i - 1; j++) {
            if (arr[j] > arr[j + 1]) {
                // Swap the elements if they are in the wrong order
                temp = arr[j];
                arr[j] = arr[j + 1];
                arr[j + 1] = temp;
            }
        }
    }
}

int main() {
    int diskSize, currentPosition, totalRequests;

    printf("Enter the size of the disk: ");
    scanf("%d", &diskSize);

    printf("Enter the current position of the disk arm: ");
    scanf("%d", &currentPosition);

    printf("Enter the total number of disk requests: ");
    scanf("%d", &totalRequests);

    int requests[totalRequests];
    int i;

    printf("Enter the disk request track numbers:\n");
    for (i = 0; i < totalRequests; i++) {
        scanf("%d", &requests[i]);
    }

    // Sort the disk requests in ascending order
    sort(requests, totalRequests);

    int seekCount = 0;

    // C-SCAN towards the right
    for (i = currentPosition; i <= diskSize; i++) {
        printf("Servicing track %d\n", i);
        seekCount += abs(currentPosition - i);
        currentPosition = i;
    }

    // Jump to the beginning of the disk
    printf("Jump to the beginning of the disk\n");
    seekCount += currentPosition;
    currentPosition = 0;

    // C-SCAN towards the right again
    for (i = currentPosition; i <= diskSize; i++) {
        printf("Servicing track %d\n", i);
        seekCount += abs(currentPosition - i);
        currentPosition = i;
    }

    printf("Total seek count: %d\n", seekCount);

    return 0;
}

