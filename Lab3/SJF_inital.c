#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

typedef struct {
    int process_id;
    int arrival_time;
    int burst_time;
    int remaining_time;
    int waiting_time;
    int turnaround_time;
    int is_completed;
} Process;

int n; // Number of processes
// Order of Processes
int processOrder[4];

// Function to find the index of the process with the shortest remaining time
int findNextProcess(Process proc[], int current_time) {
    int min_time = INT_MAX;
    int index = -1;
    for (int i = 0; i < n; i++) {
        if (proc[i].arrival_time <= current_time && // Process has arrived
            proc[i].remaining_time > 0 &&         // Process is not yet completed
            proc[i].remaining_time < min_time) {  // Shortest remaining time so far
            
            min_time = proc[i].remaining_time;
            index = i;
        }
    }
    // Return index of the shortest task
    return index;
}

// Function to perform the SRTF scheduling
void srtf(Process proc[]) {
    int current_time = 0;
    int completed = 0;
    int prev = -1;
    int k = 0;

    // Initialize average waiting and turnaround times
    int totalWaitingTime = 0;
    int totalTurnaroundTime = 0;

    // Build the loop to execute processes in the queue list
    while (completed != n) {
        // Check for process arrival
        for (int i = 0; i < n; i++) {
            // Process arrival
            if ((current_time >= proc[i].arrival_time) && (proc[i].is_completed == -1)) {
                // Remaining time
                proc[i].remaining_time = proc[i].burst_time;
                // Waiting time
                proc[i].waiting_time = 0;
                // Turnaround time
                proc[i].turnaround_time = 0;
                // Is completed - 0 for not completed
                proc[i].is_completed = 0;
            }
        }

        // Getting the next process
        int index = findNextProcess(proc, current_time);
   
        // Process found to start
        if ((prev != index) && (proc[index].is_completed == 0)) {
            printf("Time %d: Process %d starts\n", current_time, proc[index].process_id);
        }

        // Decrementing remaining time
        proc[index].remaining_time--;
        // Setting prev index
        prev = index;
        // Incrementing current time
        current_time++;

        // Process completed check
        if (proc[index].remaining_time == 0) {
            // Complete
            proc[index].is_completed = 1;
            // Turnaround time
            proc[index].turnaround_time = current_time - proc[index].arrival_time;
            // Adding into sum turnaround time
            totalTurnaroundTime += proc[index].turnaround_time;
            // Adding into sum waiting time
            totalWaitingTime += proc[index].waiting_time;
            // Updating order
            processOrder[k++] = proc[index].process_id;
            // Printing result
            printf("Time %d: Process %d completes\n", current_time, proc[index].process_id);
            // Incrementing process completed
            completed++;
        }
        // Loop to update waiting times
        for (int i = 0; i < n; i++) {
            if (proc[i].is_completed == 0 && i != index) {
                // Update individual waiting time
                proc[i].waiting_time++;
            }
        }
    }

    // Calculating average wait time and turnaround time
    printf("\nAverage waiting time: %lf\n", (double) totalWaitingTime / n);
    printf("Average turnaround time: %lf\n\n", (double) totalTurnaroundTime / n);
}

// Function to print the processes and their details
void printProcesses(Process proc[]) {
    printf("Process ID\tArrival Time\tBurst Time\tWaiting Time\tTurnaround Time\n");
    for (int i = 0; i < n; i++) {
        printf("%d\t\t%d\t\t%d\t\t%d\t\t%d\n",
               proc[i].process_id, proc[i].arrival_time, proc[i].burst_time,
               proc[i].waiting_time, proc[i].turnaround_time);
    }
}

int main() {
    // Initialize processes with their IDs, arrival times, and burst times
    Process proc[] = {{1, 0, 8, -1, -1, -1, -1},
                      {2, 1, 4, -1, -1, -1, -1},
                      {3, 2, 9, -1, -1, -1, -1},
                      {4, 3, 5, -1, -1, -1, -1}
                     };
    n = sizeof(proc) / sizeof(proc[0]);

    //Title
    printf("\n###SJF Simulation\n");
    // Simulating algorithm
    srtf(proc);
    // Printing the Process Results
    printProcesses(proc);

    //Printing completion order
    printf("\nProcess Completion Order: ");
    for (int i = 0; i < n; i++) {
        printf("%d ", processOrder[i]);
    }
    printf("\n");

    return 0;
}
