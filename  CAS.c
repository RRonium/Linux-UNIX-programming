#include <stdio.h>
#include <stdatomic.h>
#include <unistd.h>
#include <pthread.h>

#define N 5

atomic_int lock=0;
int shared_counter=0;
void* process(void* arg)
{
    int id=*(int*)arg; 

    for(int c=0;c<3;c++)
    {
        //Entry Section
        int expected=0;
        int desired=1;

        while(!atomic_compare_exchange_strong(&lock,&expected,desired))
            expected=0;
        
        //Critical Section
        shared_counter++;
        printf("Thread %d entered CS. Shared counter: %d\n",id,shared_counter);
        usleep(500000);

        //Exit Section
        atomic_store(&lock,0);

        //Remaining Section(Simulation)
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
        pthread_join(threads[i],NULL);
    
    printf("\nFinal Result: %d\n",shared_counter);
    return 0;
}