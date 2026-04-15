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
int main() {
    pthread_t r_tid[5], w_tid[5]; 
    int ids[5];

    // Initialize the semaphore (1 = available) and mutex
    sem_init(&rw_mutex, 0, 1);
    pthread_mutex_init(&mutex, NULL);

    // Create 5 Reader threads and 5 Writer threads
    for (int i = 0; i < 5; i++) {
        ids[i] = i + 1;
        pthread_create(&r_tid[i], NULL, reader, &ids[i]);
        pthread_create(&w_tid[i], NULL, writer, &ids[i]);
    }

    // Wait for all threads to finish
    for (int i = 0; i < 5; i++) {
        pthread_join(r_tid[i], NULL);
        pthread_join(w_tid[i], NULL);
    }

    // Cleanup
    sem_destroy(&rw_mutex);
    pthread_mutex_destroy(&mutex);

    return 0;
}