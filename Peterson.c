#include <stdio.h>
#include <stdbool.h>
#include <unistd.h>
#include <pthread.h>
volatile bool flag[2]={false,false};
volatile int turn=0;
int shared_counter=0;
void* process(void* arg)
{
    int i=*(int*)arg;
    int j=1-i;

    for(int c=0;c<5;c++)
    {
        //Entry Section
        flag[i]=true;
        turn=j;
        while(flag[j] && turn==j)   //Busy Waiting
        {
            printf("Process %d is in CS and %d is waiting, Standby...\n",j,i);
            usleep(100000);
        } 
        
        //Critical Section
        shared_counter++;
        printf("Process %d is executing its CS, shared counter: %d\n",i,shared_counter);
        usleep(500000);

        //Exit Section
        printf("<<<Process %d is leaving.\n",i);
        flag[i]=false;

        //Remaining Section(Simulation)
        usleep(100000);
    }
    return NULL;
}
int main()
{
    pthread_t t0,t1;
    int id0=0;
    int id1=1;
    pthread_create(&t0,NULL,process,&id0); 
    pthread_create(&t1,NULL,process,&id1);

    pthread_join(t0,NULL);
    pthread_join(t1,NULL);

    printf("Final Result: %d\n",shared_counter);
    return 0;
}