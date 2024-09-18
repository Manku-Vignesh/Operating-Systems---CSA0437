#include <stdio.h>
#include <stdlib.h>

#define PAGE_FRAMES 3
#define PAGE_REFERENCE_STRING_SIZE 10

void displayPageTable(int pageTable[], int frames) {
    printf("Page Table: ");
    for (int i = 0; i < frames; i++) {
        if (pageTable[i] == -1) {
            printf("[ ] ");
        } else {
            printf("[%d] ", pageTable[i]);
        }
    }
    printf("\n");
}

int isPageInMemory(int page, int pageTable[], int frames) {
    for (int i = 0; i < frames; i++) {
        if (pageTable[i] == page) {
            return 1; // Page found in memory
        }
    }
    return 0; // Page not found in memory
}

int findLRUPage(int pageAccessOrder[], int frames) {
    int minIndex = 0;
    for (int i = 1; i < frames; i++) {
        if (pageAccessOrder[i] < pageAccessOrder[minIndex]) {
            minIndex = i;
        }
    }
    return minIndex;
}

void simulateLRU(int pageReferenceString[], int frames, int references) {
    int pageTable[frames];
    int pageAccessOrder[frames];
    int pageFaults = 0;

    for (int i = 0; i < frames; i++) {
        pageTable[i] = -1; // Initialize page table with -1 (indicating an empty frame)
        pageAccessOrder[i] = 0; // Initialize page access order
    }

    printf("Simulating LRU Paging:\n");

    for (int i = 0; i < references; i++) {
        int page = pageReferenceString[i];

        if (!isPageInMemory(page, pageTable, frames)) {
            pageFaults++;
            int replaceIndex = findLRUPage(pageAccessOrder, frames);
            pageTable[replaceIndex] = page;
            pageAccessOrder[replaceIndex] = i + 1; // Update page access order
            displayPageTable(pageTable, frames);
        } else {
            // Page hit, update access order
            for (int j = 0; j < frames; j++) {
                if (pageTable[j] == page) {
                    pageAccessOrder[j] = i + 1; // Update page access order
                    break;
                }
            }
        }
    }

    printf("Total Page Faults: %d\n", pageFaults);
}

int main() {
    int pageReferenceString[PAGE_REFERENCE_STRING_SIZE] = {1, 2, 3, 4, 1, 2, 5, 1, 2, 3};
    int references = PAGE_REFERENCE_STRING_SIZE;

    simulateLRU(pageReferenceString, PAGE_FRAMES, references);

    return 0;
}

