#include <stdio.h>

int np; // number of processes
int nb; // number of blocks

// Best Fit Allocation
int main() {
    printf("Enter number of processes: ");
    scanf("%d", &np);
    int p[np]; // array for process sizes

    for (int i = 0; i < np; i++) {
        printf("Enter size of process %d: ", i);
        scanf("%d", &p[i]);
    }

    printf("Enter number of blocks: ");
    scanf("%d", &nb);
    int b[nb], bf[nb], bn[np], frag[np];

    for (int i = 0; i < nb; i++) {
        bf[i] = 0; // block filled status
        printf("Enter size of block %d: ", i);
        scanf("%d", &b[i]);
    }

    // Initialize process allocation block numbers to -1
    for (int i = 0; i < np; i++) {
        bn[i] = -1;
    }

    // Best Fit Allocation
    for (int i = 0; i < np; i++) {
        int smallest = 100000; // arbitrarily large number
        for (int j = 0; j < nb; j++) {
            if (bf[j] == 0 && b[j] >= p[i]) {
                if (b[j] < smallest) {
                    bn[i] = j;
                    smallest = b[j];
                }
            }
        }
        if (bn[i] != -1) {
            frag[i] = b[bn[i]] - p[i];
            bf[bn[i]] = 1;
        } else {
            frag[i] = -1; // indicates not allocated
        }
    }

    // Output Allocation Result
    printf("\nProcess_No.  Process_Size  Block_No.  Block_Size  Fragmentation\n");
    for (int i = 0; i < np; i++) {
        if (bn[i] != -1) {
            printf("%-12d %-13d %-10d %-12d %-13d\n", i, p[i], bn[i], b[bn[i]], frag[i]);
        } else {
            printf("%-12d %-13d Not Allocated\n", i, p[i]);
        }
    }

    return 0;
}
