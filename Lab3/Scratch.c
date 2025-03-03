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

int main() {
    Process proc[] = {{1, 0, 8}, {2, 1, 4}, {3, 2, 9}, {4, 3, 5}};
    n = sizeof(proc) / sizeof(proc[0]);

    printf("Burst time: %d", proc[0][2]);
    return 0;
}