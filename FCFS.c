#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct Process {
    int Pid, AT, BT, CT, StartTime, TAT, WT, RT;
};

// Function to calculate StartTime, Completion Time, TAT, WT, and RT for each process
void StartTimeCalculator(struct Process P[], int n) {
    for (int i = 0; i < n; i++) {
        if (i == 0) {
            P[i].StartTime = P[i].AT;
        } else {
            if (P[i - 1].CT < P[i].AT) {
                P[i].StartTime = P[i].AT;
            } else {
                P[i].StartTime = P[i - 1].CT;
            }
        }
        P[i].CT = P[i].StartTime + P[i].BT;         // Completion Time
        P[i].TAT = P[i].CT - P[i].AT;               // Turnaround Time
        P[i].WT = P[i].TAT - P[i].BT;               // Waiting Time
        P[i].RT = P[i].WT;                          // Response Time (same as WT in FCFS)
    }
}

// Function to draw Gantt Chart
void drawGanttChart(struct Process P[], int n) {
    printf("\nGantt Chart:\n");

    // Top bar
    printf(" ");
    for (int i = 0; i < n; i++) {
        printf("--------");
    }

    // Process IDs
    printf("\n|");
    for (int i = 0; i < n; i++) {
        printf("  P%d  |", P[i].Pid);
    }

    // Bottom bar
    printf("\n ");
    for (int i = 0; i < n; i++) {
        printf("--------");
    }

    // Time stamps
    printf("\n%d", P[0].StartTime);
    for (int i = 0; i < n; i++) {
        printf("      %d", P[i].CT);
    }
    printf("\n");

    
}

int main() {
    printf("First Come First Serve (FCFS) Scheduling Algorithm\n");
    printf("No of Processes: ");
    int n;
    scanf("%d", &n);
    struct Process P[n];

    // Step 2: Input process information for each process
    printf("Enter process info for each process (Pid, Arrival Time, Burst Time):\n");
    for (int i = 0; i < n; i++) {
        printf("Process %d:\n", i + 1);
        printf("Pid: ");
        scanf("%d", &P[i].Pid);
        printf("Arrival Time: ");
        scanf("%d", &P[i].AT);
        printf("Burst Time: ");
        scanf("%d", &P[i].BT);
    }

    // Displaying original values
    printf("\nProcess Information:\n");
    printf("Pid\tArrival Time\tBurst Time\n");
    for (int i = 0; i < n; i++) {
        printf("%d\t%d\t\t%d\n", P[i].Pid, P[i].AT, P[i].BT);
    }

    // Step 3: Calculate times
    StartTimeCalculator(P, n);

    // Display complete process info
    printf("\nComplete Process Information:\n");
    printf("Pid\tArrival Time\tBurst Time\tCompletion Time\tTurnAround Time\tWaiting Time\tResponse Time\n");
    for (int i = 0; i < n; i++) {
        printf("%d\t%d\t\t%d\t\t%d\t\t%d\t\t%d\t\t%d\n",
               P[i].Pid, P[i].AT, P[i].BT, P[i].CT, P[i].TAT, P[i].WT, P[i].RT);
    }

    drawGanttChart(P, n);

    return 0;
}
