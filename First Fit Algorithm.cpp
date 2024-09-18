#include <stdio.h>

#define MAX_BLOCKS 100
#define MAX_PROCESS 100

void firstFit(int blockSize[], int m, int processSize[], int n) {
    int allocation[MAX_PROCESS];
    for (int i = 0; i < n; i++) {
        allocation[i] = -1;  // Initialize allocation array to -1 (indicating not allocated)
    }

    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            if (blockSize[j] >= processSize[i]) {
                allocation[i] = j;  // Allocate the process to the first block that fits
                blockSize[j] -= processSize[i];
                break;  // Break the loop after allocation
            }
        }
    }

    // Display the allocation result
    printf("Process No.\tProcess Size\tBlock No.\n");
    for (int i = 0; i < n; i++) {
        printf("%d\t\t%d\t\t", i + 1, processSize[i]);
        if (allocation[i] != -1) {
            printf("%d\n", allocation[i] + 1);
        } else {
            printf("Not Allocated\n");
        }
    }
}

int main() {
    int m;  // Number of memory blocks
    int n;  // Number of processes

    printf("Enter the number of memory blocks: ");
    scanf("%d", &m);

    int blockSize[MAX_BLOCKS];
    printf("Enter the size of each memory block:\n");
    for (int i = 0; i < m; i++) {
        scanf("%d", &blockSize[i]);
    }

    printf("Enter the number of processes: ");
    scanf("%d", &n);

    int processSize[MAX_PROCESS];
    printf("Enter the size of each process:\n");
    for (int i = 0; i < n; i++) {
        scanf("%d", &processSize[i]);
    }

    firstFit(blockSize, m, processSize, n);

    return 0;
}

