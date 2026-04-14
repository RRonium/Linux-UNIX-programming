#include <stdio.h>
#include <stdatomic.h>
#include <unistd.h>
#include <pthread.h>

#define N 5

atomic_int lock=0;
int shared_counter=0;

void* process(void* arg) 
{
    int i=*(int*)arg;
    for(int c=0;c<3;c++)
    {
        //Entry Section - Busy Waiting
        while(atomic_exchange(&lock,1)==1)
            usleep(100000);
        printf("Thread %d grabbed the lock!\n",i);
        
        //Critical Section
        shared_counter++;
        printf("Thread %d is executing its CS. Shared counter: %d\n",i,shared_counter);

        //Exit Section
        atomic_store(&lock,0);

        //Remainder Section(Simulation)
        usleep(100000);
    }
    return NULL;
}
int main()
{
    pthread_t threads[N];
    int ids[N];

    for(int i=0;i<N;i++)
    {
        ids[i]=i;
        pthread_create(&threads[i],NULL,process,&ids[i]);
    }
    for(int i=0;i<N;i++)
    {
        pthread_join(threads[i],NULL);
    }
    printf("Final Result: %d\n",shared_counter);
    return 0;
}