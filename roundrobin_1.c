#include<stdio.h>
#include<stdlib.h>

struct process{
    int pid,AT,BT,CT,StartTime,WT,RT,TAT;
    int remainingBT;
    int completed;
    int started;
};

int executionorder[100];
int exetimearr[100];
int exeindex=0;

void CalculateTime(struct process P[],int n,int timeQ){
    int CurrentTime=0, completed=0;
    int queue[100], front=0, rear=0;
    int visited[n];
    
    for(int i=0; i<n; i++){
        P[i].remainingBT = P[i].BT;
        P[i].completed = 0;
        P[i].started = 0;
        visited[i] = 0;
    }

    for(int i=0; i<n; i++){
        if(P[i].AT == 0){
            queue[rear++] = i;  // 🔧 FIX: Use index instead of pid
            visited[i] = 1;
        }
    }

    while(completed < n){
        if(front == rear){
            CurrentTime++;
            for(int i=0; i<n; i++){
                if(P[i].AT <= CurrentTime && visited[i] == 0){
                    queue[rear++] = i;  // 🔧 FIX: Use index instead of pid
                    visited[i] = 1;
                }
            }
            continue;  // 🔧 FIX: Avoid accessing queue when it's empty
        }

        int idx = queue[front++];  // 🔧 FIX: Now idx is the actual array index

        if(P[idx].started == 0){
            P[idx].started = 1;
            P[idx].StartTime = CurrentTime;
            P[idx].RT = P[idx].StartTime - P[idx].AT;
        }

        int exeTime = (P[idx].remainingBT < timeQ) ? P[idx].remainingBT : timeQ;
        CurrentTime += exeTime;
        P[idx].remainingBT -= exeTime;

        executionorder[exeindex] = P[idx].pid;
        exetimearr[exeindex++] = CurrentTime;

        for(int i=0; i<n; i++){
            if(P[i].AT <= CurrentTime && visited[i] == 0){
                queue[rear++] = i;  // 🔧 FIX: Use index instead of pid
                visited[i] = 1;
            }
        }

        if(P[idx].remainingBT == 0){
            P[idx].completed = 1;
            P[idx].CT = CurrentTime;
            P[idx].TAT = P[idx].CT - P[idx].AT;
            P[idx].WT = P[idx].TAT - P[idx].BT;
            completed++;
        } else {
            queue[rear++] = idx;
        }
    }
}

void drawGanttChart(struct process P[], int n) {
    printf("\nGantt Chart:\n");
    printf(" ");
    for (int i = 0; i < exeindex; i++)  // 🔧 FIX: loop should run till exeindex not n
        printf("--------");

    printf("\n|");
    for (int i = 0; i < exeindex; i++) {  // 🔧 FIX: loop should run till exeindex
        int pid = executionorder[i];
        printf("  P%d  |", pid);
    }

    printf("\n ");
    for (int i = 0; i < exeindex; i++)  // 🔧 FIX: loop should run till exeindex
        printf("--------");

    printf("\n0");  // 🔧 FIX: Start time for Gantt chart should always be 0
    for (int i = 0; i < exeindex; i++) {
        printf("      %d", exetimearr[i]);
    }
    printf("\n");
}

int main() {
    printf("Round Robin Scheduling Algorithm\n");

    int n, timeQuantum;
    printf("No of Processes: ");
    scanf("%d", &n);
    printf("Enter Time Quantum: ");
    scanf("%d", &timeQuantum);

    struct process P[n];

    // Input
    printf("Enter process info for each process (Pid, Arrival Time, Burst Time):\n");
    for (int i = 0; i < n; i++) {
        printf("Process %d:\n", i + 1);
        P[i].pid = i + 1;
        printf("Arrival Time: ");
        scanf("%d", &P[i].AT);
        printf("Burst Time: ");
        scanf("%d", &P[i].BT);
        P[i].completed = 0;
    }

    CalculateTime(P, n, timeQuantum);  // 🔧 FIX: Replaced StartTimeCalculator with correct function

    // Output final stats
    printf("\nComplete Process Information:\n");
    printf("Pid\tAT\tBT\tCT\tTAT\tWT\tRT\n");
    for (int i = 0; i < n; i++) {
        printf("%d\t%d\t%d\t%d\t%d\t%d\t%d\n",
               P[i].pid, P[i].AT, P[i].BT, P[i].CT,
               P[i].TAT, P[i].WT, P[i].RT);
    }

    drawGanttChart(P, n);

    return 0;
}
