#include <stdio.h>
#include <stdlib.h>
int main() 
{
    int k=0, a=0, b=0, instance[5], availablity[5], allocated[10][5], need[10][5];
    int MAX[10][5], process, P[10], no_of_resources, cnt=0, i, j, op[5];

    printf("\n Enter the number of resources: ");
    scanf("%d", &no_of_resources);

    printf("\n Enter the max instances of each resources: \n ");
    for(i=0; i<no_of_resources; i++) 
    {
        availablity[i] = 0;
        printf("%c = ", (i+97));
        scanf("%d", &instance[i]); 
    }
    printf("\n Enter the number of processes: ");
    scanf("%d", &process);
    
    printf("\n Enter the allocation matrix \n ");
    for(i=0; i<no_of_resources; i++)
        printf(" %c", (i+97));
    printf("\n");

    for(i=0; i<process; i++) 
    {
        P[i] = i;
        printf("P[%d] ", P[i]);
        for(j=0; j<no_of_resources; j++) 
        {
            scanf("%d", &allocated[i][j]);
            availablity[j] += allocated[i][j];
        }
    }
    printf("\nEnter the MAX matrix \n");
    for(i=0; i<no_of_resources; i++) 
    {
        printf(" %c", (i+97));
        availablity[i] = instance[i] - availablity[i];
    }
    printf("\n");
    for(i=0; i<process; i++) 
    {
        printf("P[%d] ", i);
        for(j=0; j<no_of_resources; j++) 
        {
            scanf("%d", &MAX[i][j]);
        }
    }
    printf("\n");
    // Banker's Algorithm Safety Check Logic
    A: a = -1;
    for(i=0; i<process; i++) 
    {
        cnt = 0;
        b = P[i];
        for(j=0; j<no_of_resources; j++) 
        {
            need[b][j] = MAX[b][j] - allocated[b][j];
            if(need[b][j] <= availablity[j])
                cnt++;
        }

        if(cnt == no_of_resources) 
        {
            op[k++] = P[i];
            for(j=0; j<no_of_resources; j++)
                availablity[j] += allocated[b][j];
        } 
        else 
        {
            P[++a] = P[i];
        }
    }
    if(a != -1) 
    {
        process = a + 1;
        goto A;
    }
    printf("\t <");
    for(i=0; i<k; i++)
        printf(" P[%d] ", op[i]);
    printf(">");
    printf("\n");

    return 0;
}