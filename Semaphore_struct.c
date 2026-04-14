#include <stdio.h>
#include <unistd.h>
#include <pthread.h>
#include <stdlib.h>

#define N 5

typedef struct
{
    int value;
    int waiting_list[N];
    int list_size;
    pthread_mutex_t internal_lock;
    pthread_cond_t wait_queue;
}my_semaphore_t;
void sem_init_custom(my_semaphore_t* s, int initial_value)
{
    s->value=initial_value;
    s->list_size=0;
    pthread_mutex_init(&s->internal_lock,NULL);
    pthread_cond_init(&s->wait_queue,NULL);
}
void sem_wait_custom(my_semaphore_t* s, int thread_id)
{
    pthread_mutex_lock(&s->internal_lock); 
    s->value--;

    if(s->value<0)
    {
        s->waiting_list[s->list_size++]=thread_id;
        printf("Thread %d: Value is %d. Adding to list and sleeping...\n",thread_id,s->value);

        pthread_cond_wait(&s->wait_queue,&s->internal_lock);
    }
    pthread_mutex_unlock(&s->internal_lock);
}
void sem_signal_custom(my_semaphore_t* s, int thread_id)
{
    pthread_mutex_lock(&s->internal_lock);
    s->value++;
    if(s->value<=0)
    {
        printf("Thread %d: Signaling! Waking up a thread from the list...\n",thread_id);
        s->list_size--;
        pthread_cond_signal(&s->wait_queue);
    }
    pthread_mutex_unlock(&s->internal_lock);
}
my_semaphore_t sem;
int shared_counter=0;
void* process(void* arg)
{
    //Entry Section
    int id=*(int*)arg;
    sem_wait_custom(&sem,id); 

    //Critical Section
    printf(">>>Thread %d entered Critical Section!\n",id);
    shared_counter++;
    usleep(500000);

    //Exit Section
    printf("<<Thread %d leaving Critical Section.\n",id);
    sem_signal_custom(&sem,id);

    return NULL;
}
int main()
{
    pthread_t threads[N];
    int ids[N];

    sem_init_custom(&sem,1);

    for(int i=0;i<N;i++)
    {
        ids[i]=i;
        pthread_create(&threads[i],NULL,process,&ids[i]);
    }
    for(int i=0;i<N;i++)    pthread_join(threads[i],NULL);
    printf("\nFinal Shared Counter: %d\n",shared_counter);
    return 0;
}