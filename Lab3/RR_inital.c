// Round Robin OS Scheduling Algorithm
// @author Telmen Enkhtuvshin

#include <stdio.h>
#include <stdlib.h>

typedef struct {
    int process_id;
    int arrival_time;
    int burst_time;
    int remaining_time;
    int waiting_time;
    int turnaround_time;
} Process;



// Function to calculate waiting times and execution order for all processes
void calculateWaitingTimeAndExecutionOrder(Process proc[], int n, int quantum) {
    // Total execution time variable
    int totalTime = 0;
    // Initializing the remaining time for the processes
    for (int i = 0; i < n; i++) {
        // Remaining time
        proc[i].remaining_time = proc[i].burst_time;
        // Waiting time
        proc[i].waiting_time = 0;
        // Turnaround time
        proc[i].turnaround_time = 0;
        // Adding to totalTime
        totalTime += proc[i].burst_time;
    }

    // Assuming a maximum of 1000 executions for simplicity 
    int exeIdx = 0;
    // Storing process order in array
    int executionOrder[1000];
    // Current time
    int current_time = 0;
    // Total waiting time
    int totalWaitingTime = 0;

    // Keep traversing processes in round-robin manner until all of them are done
    while (1) {
        // Done Flag
        int done = 0;

        // Loop execution
        for (int i = 0; i < n; i++) {
            int tempTime = 0;

            // If remaining burst time of a process is greater than 0 then only need to process further
            if (proc[i].remaining_time > 0) {
                // Processing with the time quantum
                // If remaining time is equal to or less than quantum
                if (proc[i].remaining_time <= quantum) {
                    // Put process into execution order
                    executionOrder[exeIdx++] = proc[i].process_id;
                    // Put into tempTime
                    tempTime = proc[i].remaining_time;
                    // Process finished
                    proc[i].remaining_time = 0;
                    // Updating current time
                    current_time += tempTime;

                    // Process is finished, so turnaround time is calculated
                    proc[i].turnaround_time = current_time - proc[i].arrival_time;
                // Else when remaining time is greated than quantum    
                } else {
                    // Put process into execution order
                    executionOrder[exeIdx++] = proc[i].process_id;
                    // Put into tempTime
                    tempTime = quantum;
                    // Process executes
                    proc[i].remaining_time -= quantum;
                    // Updating current time
                    current_time += tempTime;
                }

                // Updating wait times for waiting processes
                for (int j = 0; j < n; j++) {
                    if ((i != j) && (proc[j].remaining_time > 0)) {
                        // Adding wait time
                        proc[j].waiting_time += tempTime;
                        // Adding wait time to total wait time
                        totalWaitingTime += tempTime;
                    }
                }
            }

            // Checking if all processes are done
            if (current_time == totalTime) done = 1;
        }

        // If all processes are done
        if (done == 1) break;

        // Infinite loop error handling
        if (exeIdx >= 1000) {
            perror("Loop iteration exceeded... Infinite loop!");
            exit(EXIT_FAILURE);
        }
    }

    // Print the execution order
    printf("Execution Order: ");
    for (int i = 0; i < exeIdx; i++) {
        printf("P%d ", executionOrder[i]);
    }
    printf("\n");

    // Info for average waiting time
    printf("\nAverage waiting time: %f\n", (float) totalWaitingTime / n);
}

// Function to calculate average turnaround times for all processes
void calculateTurnaroundTime(Process proc[], int n) {
    // Sum variable
    int totalTurnaroundTime = 0;

    // Loop for sum
    for (int i = 0; i < n; i++) {
        // Adding to total
        totalTurnaroundTime += proc[i].turnaround_time;
    }
    // Average turnaround time
    printf("Average turnaround time: %f\n\n", (float) totalTurnaroundTime / n);
}

// Function to simulate the Round Robin algorithm
void roundRobin(Process proc[], int n, int quantum) {
    // Waiting time & Execution Order
    calculateWaitingTimeAndExecutionOrder(proc, n, quantum);
    // Turnaround time
    calculateTurnaroundTime(proc, n);
}

// Function to print the Process Information
void printProcesses(Process proc[], int n) {
    printf("Process ID\tArrival Time\tBurst Time\tWaiting Time\tTurnaround Time\n");
    for (int i = 0; i < n; i++) {
        printf("%d\t\t%d\t\t%d\t\t%d\t\t%d\n",
               proc[i].process_id, proc[i].arrival_time, proc[i].burst_time,
               proc[i].waiting_time, proc[i].turnaround_time);
    }
}

int main() {
    Process proc[] = {{1, 0, 24, -1, -1, -1},
                      {2, 0, 3, -1, -1, -1},
                      {3, 0, 3, -1, -1, -1}};
    int n = sizeof(proc) / sizeof(proc[0]); // Number of processes
    int quantum = 4; // Time quantum for Round Robin scheduling
 
    // Title
    printf("\n###Round Robin Simulation\n");
    // Simulating RR algorithm
    roundRobin(proc, n, quantum);
    // Printing results
    printProcesses(proc, n);

    return 0;
}
