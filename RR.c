#include <stdio.h>
int main()
{
    int n,tq;
    int bt[10], rt[10], wt[10], tat[10];
    int time=0, completed=0;
    float avg_wt=0,avg_tat=0;
    
    printf("Enter number the processes: \n");
    scanf("%d",&n);
    printf("Enter the burst time for each of the processes: \n");
    for(int i=0;i<n;i++)
    {
        printf("P%d: ",i+1);
        scanf("%d",&bt[i]);
        rt[i]=bt[i];
        wt[i]=0;
    }

    printf("Enter the quantum: \n"); 
    scanf("%d",&tq);


    printf("Gantt Chart\n");
    printf("0");
    while(completed<n)
    {
        for(int i=0;i<n;i++)
        {
            if(rt[i]>0)
            {
                printf("--P%d--",i+1);
                if(rt[i]>tq)
                {
                    time+=tq;
                    rt[i]-=tq;
                }
                else
                {
                    time+=rt[i];
                    wt[i]=time-bt[i];
                    rt[i]=0;
                    completed++;
                }
                printf("%d",time);
            }
        }
    }

    printf("\n\nProcess\tBurst Time\tWaiting Time\tTurn Around\n");
    for(int i=0;i<n;i++)
    {
        tat[i]=bt[i]+wt[i];
        avg_wt+=wt[i];
        avg_tat+=tat[i];

        printf("P%d\t\t%d\t\t%d\t\t%d\n",i+1,bt[i],wt[i],tat[i]);
    }
        printf("\nAverage Waiting Time=%.2f",avg_wt/n);
        printf("\nAverage Turn Around Time=%.2f\n",avg_tat/n);
    
    return 0;
}