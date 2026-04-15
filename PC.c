#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <pthread.h>
#include <semaphore.h>

#define BUFFER_SIZE 5
#define N 5 


int buffer[BUFFER_SIZE];
int in=0;
int out=0;

sem_t empty;
sem_t full;
pthread_mutex_t mutex;

void* producer(void* arg)
{
    int id=*(int*)arg;
    for(int i=0;i<N;i++)
    {
        int item=rand()%100;
        sem_wait(&empty);
        pthread_mutex_lock(&mutex);

        buffer[in]=item;
        printf("Producer: %d just added a new item, %d, to the buffer at: %d\n",id,item,in);
        in=(in+1)%BUFFER_SIZE;

        pthread_mutex_unlock(&mutex);
        sem_post(&full);

        usleep(rand()%500000);
    }
    return NULL;
}
void* consumer(void* arg)
{
    int id=*(int*)arg;
    for(int i=0;i<N;i++)
    {
        sem_wait(&full);
        pthread_mutex_lock(&mutex);

        int item=buffer[out];
        printf("Consumer %d, just consumed %d from %d position of the buffer.\n",id,item,out);
        out=(out+1)%BUFFER_SIZE;

        pthread_mutex_unlock(&mutex);
        sem_post(&empty);

        usleep(rand()%500000);
    }
    return NULL;
}
int main() 
{
    pthread_t prod[N];
    pthread_t cons[N];
    int ids[N];

    sem_init(&empty, 0, BUFFER_SIZE); 
    sem_init(&full, 0, 0);
    pthread_mutex_init(&mutex, NULL);

    for(int i=0; i<N;i++)
    {
        ids[i] = i;
        pthread_create(&prod[i], NULL, producer, &ids[i]);
        pthread_create(&cons[i], NULL, consumer, &ids[i]);
    }

    for(int i=0;i<N;i++) 
    {
        pthread_join(prod[i], NULL);
        pthread_join(cons[i], NULL);
    }

    sem_destroy(&empty);
    sem_destroy(&full);
    pthread_mutex_destroy(&mutex);

    return 0;
}