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

int findFIFOPage(int pageTable[], int frames) {
    return 0; // FIFO replaces the page at the front of the queue
}

void simulateFIFO(int pageReferenceString[], int frames, int references) {
    int pageTable[frames];
    int pageQueue[frames];
    int pageFaults = 0;
    int queueIndex = 0;

    for (int i = 0; i < frames; i++) {
        pageTable[i] = -1; // Initialize page table with -1 (indicating an empty frame)
        pageQueue[i] = -1; // Initialize page queue with -1 (indicating an empty slot)
    }

    printf("Simulating FIFO Paging:\n");

    for (int i = 0; i < references; i++) {
        int page = pageReferenceString[i];

        if (!isPageInMemory(page, pageTable, frames)) {
            pageFaults++;
            int replaceIndex = findFIFOPage(pageTable, frames);

            // Update the page table and queue
            pageTable[replaceIndex] = page;
            pageQueue[queueIndex] = replaceIndex;
            queueIndex = (queueIndex + 1) % frames;

            displayPageTable(pageTable, frames);
        }
    }

    printf("Total Page Faults: %d\n", pageFaults);
}

int main() {
    int pageReferenceString[PAGE_REFERENCE_STRING_SIZE] = {1, 2, 3, 4, 1, 2, 5, 1, 2, 3};
    int references = PAGE_REFERENCE_STRING_SIZE;

    simulateFIFO(pageReferenceString, PAGE_FRAMES, references);

    return 0;
}

