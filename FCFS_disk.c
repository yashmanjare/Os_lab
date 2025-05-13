#include<stdio.h>
#include<stdlib.h>
int main()
{
    int n;
    int head, totalmov=0;
    printf("Enter no of disk requests \n");
    scanf("%d", &n);
    int diskReq[n];
    

    for(int i=0;i<n;i++)
    {
        scanf("%d", &diskReq[i]);
    }
    printf("Enter the position of head initially \n");
    scanf("%d", &head);
    printf("Head movement: %d", head);
    for(int i=0;i<n;i++)
    {
        int c=diskReq[i];
        totalmov+=abs(c-head);
        head=c;
        printf("-> %d", head);
    }
    printf("Total head movements that occured: %d", totalmov);

    return 0;
}











