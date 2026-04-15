#include <stdio.h>
int main()
{
    int n,p[20],pr[20],wt[20],tat[20],bt[20];
    float avgwt=0,avgtat=0;

    printf("Enter the no. of processes: \n");
    scanf("%d",&n);

    for(int i=0;i<n;i++)
    {
        p[i]=i+1;
        printf("Enter the burst time for process: %d\n",p[i]);
        scanf("%d",&bt[i]);
        printf("Enter the priority of the process: %d\n",p[i]);
        scanf("%d",&pr[i]);
    }

    for(int i=0;i<n-1;i++)
    {
        for(int j=0;j<n-i-1;j++)
        {
            if(pr[j+1]<pr[j])
            {
                int temp;
                temp=pr[j];
                pr[j]=pr[j+1]; 
                pr[j+1]=temp;

                temp=bt[j];
                bt[j]=bt[j+1];
                bt[j+1]=temp;

                temp=p[j];
                p[j]=p[j+1];
                p[j+1]=temp;
            }
        }
    }

    wt[0]=0;
    for(int i=1;i<n;i++)
    {
        wt[i]=0;
        for(int j=0;j<i;j++)
            wt[i]+=bt[j];
    }

    for(int i=0;i<n;i++)
    {
        tat[i]=bt[i]+wt[i];
        avgwt+=wt[i];
        avgtat+=tat[i];
        printf("\nP:%d | Priority:%d | BT:%d | WT:%d | TAT:%d |\n",p[i],pr[i],bt[i],wt[i],tat[i]);
    }
    printf("Avg WT:%.2f\n",(avgwt/n));
    printf("Avg TAT:%.2f\n",(avgtat/n));

    return 0;
}