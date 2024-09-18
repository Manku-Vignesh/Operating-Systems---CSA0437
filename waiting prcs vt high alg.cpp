#include <stdio.h>
#include <stdlib.h>

// Process structure to store process details
struct Process {
    int processID;
    int arrivalTime;
    int burstTime;
    int priority;
};

// Function to perform Priority Scheduling
void priorityScheduling(struct Process processes[], int n) {
    int currentTime = 0;  // Current time
    int totalWaitingTime = 0;  // Total waiting time for all processes
    int totalTurnaroundTime = 0;  // Total turnaround time for all processes

    // Sort processes based on priority (higher priority first)
    for (int i = 0; i < n - 1; i++) {
        for (int j = 0; j < n - i - 1; j++) {
            if (processes[j].priority < processes[j + 1].priority) {
                // Swap processes if not in the correct order
                struct Process temp = processes[j];
                processes[j] = processes[j + 1];
                processes[j + 1] = temp;
            }
        }
    }

    // Perform Priority Scheduling
    for (int i = 0; i < n; i++) {
        // Wait until the process arrives
        while (currentTime < processes[i].arrivalTime) {
            currentTime++;
        }

        // Update waiting time for the current process
        processes[i].waitingTime = currentTime;

        // Update turnaround time for the current process
        processes[i].turnaroundTime = processes[i].waitingTime + processes[i].burstTime;

        // Update total waiting and turnaround times
        totalWaitingTime += processes[i].waitingTime;
        totalTurnaroundTime += processes[i].turnaroundTime;

        // Move to the next process
        currentTime += processes[i].burstTime;
    }

    // Display results
    printf("Process\tArrival Time\tBurst Time\tPriority\tWaiting Time\tTurnaround Time\n");
    for (int i = 0; i < n; i++) {
        printf("%d\t%d\t\t%d\t\t%d\t\t%d\t\t%d\n", processes[i].processID, processes[i].arrivalTime,
               processes[i].burstTime, processes[i].priority, processes[i].waitingTime, processes[i].turnaroundTime);
    }

    // Calculate and display average waiting and turnaround times
    float avgWaitingTime = (float)totalWaitingTime / n;
    float avgTurnaroundTime = (float)totalTurnaroundTime / n;

    printf("Average Waiting Time: %.2f\n", avgWaitingTime);
    printf("Average Turnaround Time: %.2f\n", avgTurnaroundTime);
}

int main() {
    // Number of processes
    int n;

    printf("Enter the number of processes: ");
    scanf("%d", &n);

    struct Process processes[n];

    // Input process details
    for (int i = 0; i < n; i++) {
        processes[i].processID = i + 1;
        printf("Enter arrival time for process %d: ", i + 1);
        scanf("%d", &processes[i].arrivalTime);
        printf("Enter burst time for process %d: ", i + 1);
        scanf("%d", &processes[i].burstTime);
        printf("Enter priority for process %d: ", i + 1);
        scanf("%d", &processes[i].priority);
    }

    // Perform Priority Scheduling
    priorityScheduling(processes, n);

    return 0;
}

