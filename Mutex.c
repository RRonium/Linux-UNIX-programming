#include <stdio.h>
#include <unistd.h>
#include <pthread.h>

#define N 5

pthread_mutex_t my_mutex=PTHREAD_MUTEX_INITIALIZER;
int shared_counter=0;

void* process(void* arg)
{
    int id=*(int*)arg;
    for(int c=0;c<3;c++)
    {
        //Entry Section
        pthread_mutex_lock(&my_mutex);
        printf("Thread %d grabbed the lock.\n",id);

        //Critical Section
        shared_counter++;
        printf("Thread %d is in CS. Shared counter: %d\n",id,shared_counter);
        usleep(500000);

        //Exit Section
        pthread_mutex_unlock(&my_mutex);
        printf("Thread %d has released the lock.\n",id);

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
        if(pthread_create(&threads[i],NULL,process,&ids[i])!=0)
        {
            perror("Thread Creation Failure!\n");
            return 1;
        }
    }
    for(int i=0;i<N;i++)
        pthread_join(threads[i],NULL);
    
        pthread_mutex_destroy(&my_mutex);
        printf("\nFinal Result: %d\n",shared_counter);
        return 0;
}