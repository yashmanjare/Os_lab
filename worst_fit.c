#include <stdio.h>

int np; // number of processes
int nb; // number of memory blocks

// Worst Fit Allocation
int main() {
    printf("Enter number of processes: ");
    scanf("%d", &np);
    int p[np]; // process sizes

    for (int i = 0; i < np; i++) {
        printf("Enter size of process %d: ", i);
        scanf("%d", &p[i]);
    }

    printf("Enter number of blocks: ");
    scanf("%d", &nb);
    int b[nb], bf[nb], bn[np], frag[np];

    for (int i = 0; i < nb; i++) {
        printf("Enter size of block %d: ", i);
        scanf("%d", &b[i]);
        bf[i] = 0; // block allocation flag (0 = free, 1 = allocated)
    }

    // Initialize process block numbers to -1 (not allocated)
    for (int i = 0; i < np; i++) {
        bn[i] = -1;
    }

    // Worst Fit Allocation Logic
    for (int i = 0; i < np; i++) {
        int largest = 0;
        for (int j = 0; j < nb; j++) {
            if (bf[j] == 0 && b[j] >= p[i]) {
                if (b[j] > largest) {
                    bn[i] = j;
                    largest = b[j];
                }
            }
        }
        if (bn[i] != -1) {
            frag[i] = b[bn[i]] - p[i];
            bf[bn[i]] = 1; // mark block as allocated
        } else {
            frag[i] = -1; // not allocated
        }
    }

    // Output results
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
