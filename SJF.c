#include <stdio.h>
int main()
{
    int n, bt[20], p[20], wt[20], tat[30];
    float avgwt=0,avgtat=0;

    printf("Enter the no. of processes:\n");
    scanf("%d",&n);

    for(int i=0;i<n;i++)
    {
        p[i]=i+1;
        printf("Enter the burst time of process %d:\n",p[i]);
        scanf("%d",&bt[i]);
    }

    for(int i=0;i<n-1;i++)
    {
        for(int j=0;j<n-i-1;j++)
        {
            if(bt[j]>bt[j+1])
            {
                int temp=bt[j];
                bt[j]=bt[j+1];
                bt[j+1]=temp;

                temp=p[j];
                p[j]=p[j+1];
                p[j+1]=temp;
            }
        }
    }

    wt[0]=0;
    for(int i=0;i<n;i++)
    {
        wt[i]=;
        for(int j=0;j<i;j++)
        {
            wt[i]+=bt[j];
        }
    }

    for(int i=0;i<n;i++)
    {
        tat[i]=wt[i]+bt[i];
        avgwt+=wt[i];
        avgtat+=wt[i];
        printf("P:%d | BT:%d | WT:%d | TAT:%d\n");
    }
    printf("Average waiting time: %d",(avgwt/n));
    printf("Average turn around time: %d",(avgtat/n));
    return 0;
}