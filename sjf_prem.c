#include <stdio.h>
#include <stdlib.h>

struct Process {
    int Pid, AT, BT, CT, StartTime, TAT, WT, RT;
    int completed, remainingBT, started;
};

int executionOrder[100];

void StartTimeCalculator(struct Process P[], int n) {
    int currentTime = 0, completedCount = 0, executionIndex = 0;

    for (int i = 0; i < n; i++) {
        P[i].remainingBT = P[i].BT;
        P[i].completed = 0;
        P[i].started = 0;
    }

    while (completedCount < n) {
        int idx = -1;
        int minBT = 1e9;

        for (int i = 0; i < n; i++) {
            if (P[i].AT <= currentTime && !P[i].completed && P[i].remainingBT < minBT) {
                minBT = P[i].remainingBT;
                idx = i;
            }
        }

        if (idx == -1) {
            currentTime++;
        } else {
            if (!P[idx].started) {
                P[idx].StartTime = currentTime;
                P[idx].RT = currentTime - P[idx].AT;
                P[idx].started = 1;
            }

            P[idx].remainingBT--;
            executionOrder[executionIndex++] = idx;
            currentTime++;

            if (P[idx].remainingBT == 0) {
                P[idx].CT = currentTime;
                P[idx].TAT = P[idx].CT - P[idx].AT;
                P[idx].WT = P[idx].TAT - P[idx].BT;
                P[idx].completed = 1;
                completedCount++;
            }
        }
    }
}

void drawGanttChart(struct Process P[], int n) {
    printf("\nGantt Chart:\n");

    // Top bar
    printf(" ");
    for (int i = 0; i < n * 10; i++) printf("-");

    // Process IDs
    printf("\n|");
    int i = 0;
    while (executionOrder[i] != -1) {
        int j = i;
        while (executionOrder[j] == executionOrder[i]) j++;
        printf(" P%d |", P[executionOrder[i]].Pid);
        i = j;
    }

    // Bottom bar
    printf("\n ");
    for (int i = 0; i < n * 10; i++) printf("-");

    // Time stamps
    printf("\n0");
    i = 0;
    int time = 0;
    while (executionOrder[i] != -1) {
        int j = i;
        while (executionOrder[j] == executionOrder[i]) j++;
        time += (j - i);
        printf("     %2d", time);
        i = j;
    }
    printf("\n");
}

int main() {
    printf("Preemptive SJF (SRTF) Scheduling Algorithm\n");
    printf("Number of Processes: ");
    int n;
    scanf("%d", &n);
    struct Process P[n];

    printf("Enter process info (Pid, Arrival Time, Burst Time):\n");
    for (int i = 0; i < n; i++) {
        printf("Process %d:\n", i + 1);
        printf("Pid: ");
        scanf("%d", &P[i].Pid);
        printf("Arrival Time: ");
        scanf("%d", &P[i].AT);
        printf("Burst Time: ");
        scanf("%d", &P[i].BT);
    }

    // Initialize execution order array
    for (int i = 0; i < 100; i++) executionOrder[i] = -1;

    StartTimeCalculator(P, n);

    printf("\nComplete Process Information:\n");
    printf("Pid\tAT\tBT\tCT\tTAT\tWT\tRT\n");
    for (int i = 0; i < n; i++) {
        printf("%d\t%d\t%d\t%d\t%d\t%d\t%d\n",
               P[i].Pid, P[i].AT, P[i].BT, P[i].CT,
               P[i].TAT, P[i].WT, P[i].RT);
    }

    drawGanttChart(P, n);

    return 0;
}
