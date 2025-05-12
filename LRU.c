#include <stdio.h> 
 
int main() { 
    int np, nf, faults = 0, cnt = 0; 
    int P[30], F[10], time[10]; 
    int i, j, k, flag, flag2, loc, minimum; 
 
    // Accept number of pages and number of frames 
    printf("Enter number of pages: "); 
    scanf("%d", &np); 
    printf("Enter the page reference string: "); 
    for(i = 0; i < np; i++) 
        scanf("%d", &P[i]); 
 
    printf("Enter number of frames: "); 
    scanf("%d", &nf); 
 
    // Initialize frames and time arrays 
    for(i = 0; i < nf; i++) { 
        F[i] = -1; 
        time[i] = 0; 
    } 
 
    printf("\nPage\tFrame Contents\n"); 
  
 
    // Loop through each page 
    for(i = 0; i < np; i++) { 
        flag = flag2 = 0; 
 
        // Page Hit 
        for(j = 0; j < nf; j++) { 
            if(P[i] == F[j]) { 
                cnt++; 
                time[j] = cnt; 
                flag = flag2 = 1; 
                break; 
            } 
        } 
 
        // If free frame available 
        if(flag2 == 0) { 
            for(j = 0; j < nf; j++) { 
                if(F[j] == -1) { 
                    F[j] = P[i]; 
                    cnt++; 
                    time[j] = cnt; 
                    faults++; 
                    flag = flag2 = 1; 
                    break; 
                } 
            } 
        } 
 
        // Page replacement using LRU 
        if(flag2 == 0) { 
            minimum = 1000; 
            for(j = 0; j < nf; j++) { 
                if(time[j] < minimum) { 
                    minimum = time[j]; 
                    loc = j; 
                } 
            } 
            F[loc] = P[i]; 
            cnt++; 
            time[loc] = cnt; 
            faults++; 
        } 
 
        // Display current frame status 
        printf("%d\t\t", P[i]); 
        for(k = 0; k < nf; k++) { 
            if(F[k] != -1) 
                printf("%d  ", F[k]); 
            else 
                printf("-1 "); 
        } 
        printf("\n"); 
    } 
 
    printf("Total Page Faults = %d\n", faults); 
    printf("Total page hit = %d\n",np-faults); 
    return 0; 
} 
