#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct Process {
    int Pid, AT, BT, CT, StartTime, TAT, WT, RT;
    int priority;     // ✅ Added priority field
    int completed;    // Completion flag
};

int executionOrder[100];

void StartTimeCalculator(struct Process P[], int n) {
    int currentTime = 0, completedCount = 0;

    while (completedCount < n) {
        int idx = -1;
        int highestPriority = 1e9;

        for (int i = 0; i < n; i++) {
            if (P[i].AT <= currentTime && P[i].completed == 0) {
                if (P[i].priority < highestPriority || 
                   (P[i].priority == highestPriority && P[i].AT < P[idx].AT)) {
                    highestPriority = P[i].priority;
                    idx = i;
                }
            }
        }

        if (idx == -1) {
            currentTime++;
        } else {
            P[idx].StartTime = currentTime;
            P[idx].CT = P[idx].StartTime + P[idx].BT;
            P[idx].TAT = P[idx].CT - P[idx].AT;
            P[idx].WT = P[idx].TAT - P[idx].BT;
            P[idx].RT = P[idx].WT;
            P[idx].completed = 1;

            executionOrder[completedCount] = idx;
            currentTime = P[idx].CT;
            completedCount++;
        }
    }
}

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
        int idx = executionOrder[i];
        printf("  P%d  |", P[idx].Pid);
    }

    // Bottom bar
    printf("\n ");
    for (int i = 0; i < n; i++) {
        printf("--------");
    }

    // Time stamps
    printf("\n%d", P[executionOrder[0]].StartTime);
    for (int i = 0; i < n; i++) {
        printf("      %d", P[executionOrder[i]].CT);
    }
    printf("\n");
}

int main() {
    printf("Priority Scheduling Algorithm (Non-Preemptive)\n");
    printf("No of Processes: ");
    int n;
    scanf("%d", &n);
    struct Process P[n];

    // Input
    printf("Enter process info for each process (Pid, Arrival Time, Burst Time, Priority):\n");
    for (int i = 0; i < n; i++) {
        printf("Process %d:\n", i + 1);
        printf("Pid: ");
        scanf("%d", &P[i].Pid);
        printf("Arrival Time: ");
        scanf("%d", &P[i].AT);
        printf("Burst Time: ");
        scanf("%d", &P[i].BT);
        printf("Priority (lower = higher priority): ");
        scanf("%d", &P[i].priority);
        P[i].completed = 0;
    }

    // Display input
    printf("\nProcess Information:\n");
    printf("Pid\tArrival Time\tBurst Time\tPriority\n");
    for (int i = 0; i < n; i++) {
        printf("%d\t%d\t\t%d\t\t%d\n", P[i].Pid, P[i].AT, P[i].BT, P[i].priority);
    }

    StartTimeCalculator(P, n);

    // Display output
    printf("\nComplete Process Information:\n");
    printf("Pid\tArrival Time\tBurst Time\tPriority\tCompletion Time\tTAT\tWT\tRT\n");
    for (int i = 0; i < n; i++) {
        printf("%d\t%d\t\t%d\t\t%d\t\t%d\t\t%d\t%d\t%d\n",
               P[i].Pid, P[i].AT, P[i].BT, P[i].priority,
               P[i].CT, P[i].TAT, P[i].WT, P[i].RT);
    }

    drawGanttChart(P, n);

    return 0;
}
