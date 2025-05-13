#include <stdio.h>
#include <stdlib.h>
#define MAX 200

int main() {
    int i, n, head, tracks, pending, diff, min, index;
    int disc_seq[MAX], finish[MAX] = {0};
    int totalheadmovement = 0;

    // Input number of disk requests
    printf("Enter number of disk request: ");
    scanf("%d", &n);

    // Input disk request sequence
    printf("Enter disk sequence:\n");
    for (i = 0; i < n; i++) {
        scanf("%d", &disc_seq[i]);
    }

    // Input initial head position
    printf("Enter initial head position: ");
    scanf("%d", &head);

    // Input total number of tracks (not directly used here)
    printf("Enter total number of tracks: ");
    scanf("%d", &tracks);

    // Set number of pending requests
    pending = n;

    // SSTF Disk Scheduling Logic
    while (pending > 0) {
        min = 1000; // Arbitrary large value to find the minimum
        for (i = 0; i < n; i++) {
            if (!finish[i]) {
                diff = abs(head - disc_seq[i]);
                if (diff < min) {
                    min = diff;
                    index = i;
                }
            }
        }

        totalheadmovement += abs(head - disc_seq[index]);
        head = disc_seq[index];
        finish[index] = 1;
        pending--;

        printf("Head moves to: %d\n", head);
    }

    printf("Total head movement = %d\n", totalheadmovement);
    return 0;
}
