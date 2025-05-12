#include <stdio.h>
#include <stdbool.h>

// Function to print the system state table
void printTable(int n, int m, int allocation[n][m], int max[n][m], int need[n][m], bool finish[n], int work[m]) {
    printf("\nWork Vector :");
    for (int i = 0; i < m; i++) {
        printf(" %d", work[i]);
    }
    printf("\nProcess Allocation Max Need Finish\n");
    for (int i = 0; i < n; i++) {
        printf("P%d\t", i);
        for (int j = 0; j < m; j++) {
            printf(" %d", allocation[i][j]);
        }
        printf("\t");
        for (int j = 0; j < m; j++) {
            printf(" %d", max[i][j]);
        }
        printf("\t");
        for (int j = 0; j < m; j++) {
            printf(" %d", need[i][j]);
        }
        printf("\t");
        printf(" %s", finish[i] ? "True" : "False");
        printf("\n");
    }
    printf("-------------------------------------------------\n\n");
}

// Function to check safe state (Banker's Algorithm)
bool checkSafeState(int n, int m, int allocation[n][m], int max[n][m], int available[m], int safeSequence[n]) {
    int work[m];
    bool finish[n];
    for (int i = 0; i < m; i++) work[i] = available[i];
    for (int i = 0; i < n; i++) finish[i] = false;

    int need[n][m];
    for (int i = 0; i < n; i++)
        for (int j = 0; j < m; j++)
            need[i][j] = max[i][j] - allocation[i][j];

    int index = 0;
    while (index < n) {
        int processCount = 0;
        for (int i = 0; i < n; i++) {
            if (!finish[i]) {
                bool canProceed = true;
                for (int j = 0; j < m; j++) {
                    if (need[i][j] > work[j]) {
                        canProceed = false;
                        break;
                    }
                }
                if (canProceed) {
                    for (int j = 0; j < m; j++)
                        work[j] += allocation[i][j];
                    safeSequence[index++] = i;
                    finish[i] = true;
                    printTable(n, m, allocation, max, need, finish, work);
                    processCount++;
                }
            }
        }
        if (processCount == 0) break;
    }

    for (int i = 0; i < n; i++)
        if (!finish[i]) return false;

    return true;
}

// ✅ New: Resource request implementation
bool requestResources(int n, int m, int allocation[n][m], int max[n][m], int available[m], int p, int request[m]) {
    int need[n][m], safeSequence[n];

    for (int i = 0; i < n; i++)
        for (int j = 0; j < m; j++)
            need[i][j] = max[i][j] - allocation[i][j];

    // Check if request is within need and available
    for (int i = 0; i < m; i++) {
        if (request[i] > need[p][i]) {
            printf("Request exceeds maximum need.\n");
            return false;
        }
        if (request[i] > available[i]) {
            printf("Resources not available. Process P%d must wait.\n", p);
            return false;
        }
    }

    // Pretend to allocate requested resources
    for (int i = 0; i < m; i++) {
        available[i] -= request[i];
        allocation[p][i] += request[i];
        need[p][i] -= request[i];
    }

    // Check if the state is still safe
    if (checkSafeState(n, m, allocation, max, available, safeSequence)) {
        printf("Request granted. System is in a safe state.\n");
        return true;
    } else {
        // Rollback if unsafe
        for (int i = 0; i < m; i++) {
            available[i] += request[i];
            allocation[p][i] -= request[i];
            need[p][i] += request[i];
        }
        printf("Request denied. System would be in an unsafe state.\n");
        return false;
    }
}

// Main Function
int main() {
    int n, m;
    printf("\nEnter the number of processes: ");
    scanf("%d", &n);
    printf("Enter the number of resource types: ");
    scanf("%d", &m);

    int allocation[n][m], max[n][m], available[m], safeSequence[n];

    printf("Enter allocation matrix:\n");
    for (int i = 0; i < n; i++)
        for (int j = 0; j < m; j++)
            scanf("%d", &allocation[i][j]);

    printf("Enter max matrix:\n");
    for (int i = 0; i < n; i++)
        for (int j = 0; j < m; j++)
            scanf("%d", &max[i][j]);

    printf("Enter available resources:\n");
    for (int i = 0; i < m; i++)
        scanf("%d", &available[i]);

    if (checkSafeState(n, m, allocation, max, available, safeSequence)) {
        printf("NO DEADLOCK DETECTED. System is in a safe state.\nSafe Sequence: ");
        for (int i = 0; i < n; i++)
            printf("P%d ", safeSequence[i]);
        printf("\n");
    } else {
        printf("DEADLOCK DETECTED. System is in an unsafe state.\n");
    }

    // ✅ Ask for resource request simulation
    char choice;
    printf("\nDo you want to simulate a resource request? (y/n): ");
    scanf(" %c", &choice);
    if (choice == 'y' || choice == 'Y') {
        int p, request[m];
        printf("Enter the process number (0 to %d): ", n - 1);
        scanf("%d", &p);
        printf("Enter request vector of %d resources:\n", m);
        for (int i = 0; i < m; i++)
            scanf("%d", &request[i]);

        requestResources(n, m, allocation, max, available, p, request);
    }

    return 0;
}
