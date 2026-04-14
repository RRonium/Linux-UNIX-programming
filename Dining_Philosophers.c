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