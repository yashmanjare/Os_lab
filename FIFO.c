#include <stdio.h>
int main()
{
    int nf, np, i, j, pos = 0, flag, fault = 0, hit = 0;
    int f[10], p[30];
    printf("Enter number of frames: ");
    scanf("%d", &nf);
    printf("Enter number of pages: ");
    scanf("%d", &np);
    printf("Enter page reference string:\n");
    for (i = 0; i < np; i++)
    {
        scanf("%d", &p[i]);
    }
    // Initialize frames with -1
    for (i = 0; i < nf; i++)
    {
        f[i] = -1;
    }
    printf("\t\t F1 F2 F3\n");
    for (i = 0; i < np; i++)
    {
        flag = 0;
        for (j = 0; j < nf; j++)
        {
            if (f[j] == p[i])
            {
                hit++;
                flag = 1;
                break;
            }
        }
        if (flag == 0)
        {
            f[pos] = p[i];
            fault++;
            pos++;
            if (pos == nf)
                pos = 0;
        }
        printf("Page %d => ", p[i]);
        for (j = 0; j < nf; j++)
        {
            if (f[j] != -1)
                printf("%d ", f[j]);
            else
                printf("- ");
        }
        if (flag)
            printf(" (Hit)");
        else
            printf(" (Fault)");
        printf("\n");
    }
    printf("\nTotal Page Hits = %d", hit);
    printf("\nTotal Page Faults = %d", fault);
    printf("\nHit Ratio = %.2f", (float)hit / np);
    printf("\nMiss Ratio = %.2f", (float)fault / np);
    return 0;
}