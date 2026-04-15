#include <stdio.h>
#include <stdbool.h>
#include <unistd.h>
#include <pthread.h>

#define n 5

volatile bool choosing[n]={false};
volatile int ticket[n]={0};
int shared_counter=0;

int get_max_ticket()
{
    int res=ticket[0];
    for(int i=0;i<n;i++)
        if(res<ticket[i])
            res=ticket[i];
    return res;
}
void* process(void* arg)
{
    int i=*(int*)arg;
    for(int c=0;c<3;c++)
    {
        //Entry Section
        choosing[i]=true;
        ticket[i]=get_max_ticket()+1;
        choosing[i]=false;

        //Busy Waiting
        for(int j=0;j<n;j++)
        {
            while(choosing[j]);
            while(ticket[j]!=0 && (ticket[j]<ticket[i] || (ticket[j]==ticket[i] && j<i)));
        }

        //Critical Section
        shared_counter++;
        printf("Thread %d (Ticket %d) is in CS. Shared counter: %d\n",i,ticket[i],shared_counter);
        usleep(500000);

        //Exit Section
        ticket[i]=0;

        //Remaining Section.(Simulation)
        usleep(100000);
    }
    return NULL;
}
int main()
{
    pthread_t threads[n];
    int thread_id[n];

    printf("The Simlation of the Bakery Algorithm begins\n\n");

    for(int i=0;i<n;i++)
    {
        thread_id[i]=i;
        if(pthread_create(&threads[i],NULL,process,&thread_id[i])!=0)
        {
            perror("Failure in thread creation\n");
            return 1;
        }
    }

    for(int i=0;i<n;i++)
        pthread_join(threads[i],NULL);
    
    printf("All threads are finished. Final counter: %d",shared_counter); 

    return 0;
}