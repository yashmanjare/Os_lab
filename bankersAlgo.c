#include <stdio.h>
#include <stdbool.h>
void printTable(int n, int m, int allocation[n][m], int max[n][m], int need[n][m], bool finish[n],
                int work[m])
{
    printf("\nWork Vector :");
    for (int i = 0; i < m; i++)
    {
        printf(" %d", work[i]);
    }
    printf("\nProcess Allocation Max Need Finish\n");
    for (int i = 0; i < n; i++)
    {
        printf("P%d\t", i);
        for (int j = 0; j < m; j++)
        {
            printf(" %d", allocation[i][j]);
        }
        printf("\t");
        for (int j = 0; j < m; j++)
        {
            printf(" %d", max[i][j]);
        }
        printf("\t");
        for (int j = 0; j < m; j++)
        {
            printf(" %d", need[i][j]);
        }
        printf("\t");
        printf(" %s", finish[i] ? "True" : "False");
        printf("\n");
    }
    printf("-------------------------------------------------\n\n");
}
bool checkSafeState(int n, int m, int allocation[n][m], int max[n][m], int available[m], int safeSequence[n])
{
    int work[m];
    bool finish[n];
    for (int i = 0; i < m; i++)
    {
        work[i] = available[i];
    }
    for (int i = 0; i < n; i++)
    {
        finish[i] = false;
    }
    int need[n][m];
    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < m; j++)
        {
            need[i][j] = max[i][j] - allocation[i][j];
        }
    }
    int index = 0;
    while (index < n)
    {
        int processCount = 0;
        for (int i = 0; i < n; i++)
        {
            if (!finish[i])
            {
                bool canProceed = true;
                for (int j = 0; j < m; j++)
                {
                    if (need[i][j] > work[j])
                    {
                        canProceed = false;
                        break;
                    }
                }
                if (canProceed)
                {
                    for (int j = 0; j < m; j++)
                    {
                        work[j] += allocation[i][j];
                    }
                    safeSequence[index] = i;
                    index++;
                    finish[i] = true;
                    printTable(n, m, allocation, max, need, finish, work);
                    processCount++;
                }
            }
        }
        if (processCount == 0)
        {
            break;
        }
    }
    for (int i = 0; i < n; i++)
    {
        if (!finish[i])
        {
            return false;
        }
    }
    return true;
}
int main()
{
    int n, m;
    printf("\nEnter the no of processes: ");
    scanf("%d", &n);
    printf("Enter the no of Resource types: ");
    scanf("%d", &m);
    int allocation[n][m], max[n][m], need[n][m], available[m], safeSequence[n];
    printf("Enter allocation matrix:\n");
    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < m; j++)
        {
            scanf("%d", &allocation[i][j]);
        }
    }
    printf("Enter max matrix:\n");
    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < m; j++)
        {
            scanf("%d", &max[i][j]);
        }
    }
    printf("Enter available resources:\n");
    for (int i = 0; i < m; i++)
    {
        scanf("%d", &available[i]);
    }
    if (checkSafeState(n, m, allocation, max, available, safeSequence))
    {
        printf("NO DEADLOCK DETECTED. System is in a safe state.\nSafe Sequence: ");
        for (int i = 0; i < n; i++)
        {
            printf("P%d ", safeSequence[i]);
        }
        printf("\n");
    }
    else
    {
        printf("DEADLOCK DETECTED. System is in an unsafe state.\n");
    }
    return 0;
}