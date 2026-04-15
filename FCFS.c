#include <stdio.h>
int main()
{
    int n,p[20],bt[20],wt[20],tat[20];
    float avgwt=0,avgtat=0;

    printf("Enter the no. of processes: \n");
    scanf("%d",&n);

    for(int i=0;i<n;i++)
    {
        p[i]=i+1;
        printf("Enter the burst time for the process %d:\n",bt[i]); 
        scanf("%d",&bt[i]);
    }

    wt[0]=0;
    for(int i=1;i<n;i++)
    {
        wt[i]=0;
        for(int j=0;j<i;j++)
        {
            wt[i]+=bt[j];
        }
    }
    for(int i=0;i<n;i++)
    {
        tat[i]=bt[i]+wt[i];
        avgwt+=wt[i];
        avgtat+=tat[i];
        printf("P:%d | BT:%d | WT:%d | TAT:%d \n",p[i],bt[i],wt[i],tat[i]);
    }
    printf("The average waiting time: %.2f",avgwt);
    printf("The average turn around time: %.2f",avgtat);

    return 0;
}