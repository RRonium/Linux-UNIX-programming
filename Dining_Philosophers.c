#include <stdio.h>
#include <pthread.h>
#include <semaphore.h>
#include <unistd.h>

#define N 5

sem_t chopsticks[N];

void* philosopher(void* arg) {
    int id = *(int*)arg;

    for(int i = 0; i < 3; i++) {
        printf("Philosopher %d is thinking...\n", id);
        usleep(500000);

        // --- Entry Section (Picking up chopsticks) ---
        if (id == N - 1) { 
            // The "Asymmetric" Philosopher: Right then Left
            sem_wait(&chopsticks[(id + 1) % N]); 
            sem_wait(&chopsticks[id]);
        } else {
            // Everyone else: Left then Right
            sem_wait(&chopsticks[id]);
            sem_wait(&chopsticks[(id + 1) % N]);
        }

        // --- Critical Section (Eating) ---
        printf("Philosopher %d is EATING! (Left: %d, Right: %d)\n", id, id, (id+1)%N);
        usleep(500000);

        // --- Exit Section (Putting down chopsticks) ---
        sem_post(&chopsticks[id]);
        sem_post(&chopsticks[(id + 1) % N]);
    }
    return NULL;
}
int main() 
{
    pthread_t threads[N];
    int ids[N];

    // Initialize semaphores for each chopstick to 1 (Available)
    for (int i = 0; i < N; i++) 
        sem_init(&chopsticks[i], 0, 1);
    // Create philosopher threads
    for (int i = 0; i < N; i++) 
    {
        ids[i] = i;
        if (pthread_create(&threads[i], NULL, philosopher, &ids[i]) != 0) 
        {
            perror("Failed to create thread");
            return 1;
        }
    }

    // Wait for all philosophers to finish their 3 meals
    for (int i = 0; i < N; i++) 
        pthread_join(threads[i], NULL);
    printf("\nAll philosophers have finished eating and thinking.\n");
    
    // Cleanup: Destroy semaphores
    for (int i = 0; i < N; i++) {
        sem_destroy(&chopsticks[i]);
    }

    return 0;
}