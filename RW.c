#include <stdio.h>
#include <pthread.h>
#include <semaphore.h>
#include <unistd.h>

sem_t rw_mutex;     // Controls access for the Writer
pthread_mutex_t mutex; // Protects the read_count variable
int read_count = 0;    // Number of readers currently reading

void* reader(void* arg) {
    int id = *(int*)arg;

    // -- Entry Section --
    pthread_mutex_lock(&mutex);
    read_count++;
    if (read_count == 1) {
        sem_wait(&rw_mutex); // First reader locks the writer out
    }
    pthread_mutex_unlock(&mutex);

    // -- Reading Section (Critical Section) --
    printf("Reader %d is reading the database...\n", id);
    usleep(500000); 

    // -- Exit Section --
    pthread_mutex_lock(&mutex);
    read_count--;
    if (read_count == 0) {
        sem_post(&rw_mutex); // Last reader wakes up the writer
    }
    pthread_mutex_unlock(&mutex);

    return NULL;
}

void* writer(void* arg) {
    int id = *(int*)arg;

    // -- Entry Section --
    sem_wait(&rw_mutex); // Wait for exclusive access

    // -- Writing Section (Critical Section) --
    printf("Writer %d is UPDATING the database!!!\n", id);
    usleep(1000000);

    // -- Exit Section --
    sem_post(&rw_mutex); // Release for next reader or writer

    return NULL;
}