#include <stdio.h>
#include <pthread.h>

#define NUM_THREADS 10
#define NUM_ITERATIONS 1000

int balance = 0;              // Shared balance variable
pthread_mutex_t balance_lock; // Mutex to protect balance

void* deposit(void* arg) {
    for (int i = 0; i < NUM_ITERATIONS; i++) {
        pthread_mutex_lock(&balance_lock); // Lock mutex before modifying balance
        balance += 10;                     // Deposit 10 units
        pthread_mutex_unlock(&balance_lock); // Unlock mutex after modifying balance
    }
    return NULL;
}

void* withdraw(void* arg) {
    for (int i = 0; i < NUM_ITERATIONS; i++) {
        pthread_mutex_lock(&balance_lock); // Lock mutex before modifying balance
        balance -= 10;                     // Withdraw 10 units
        pthread_mutex_unlock(&balance_lock); // Unlock mutex after modifying balance
    }
    return NULL;
}

int main() {
    pthread_t threads[NUM_THREADS];

    // Initialize the mutex
    pthread_mutex_init(&balance_lock, NULL);

    // Create threads that perform deposits and withdrawals
    for (int i = 0; i < NUM_THREADS / 2; i++) {
        pthread_create(&threads[i], NULL, deposit, NULL);
        pthread_create(&threads[NUM_THREADS / 2 + i], NULL, withdraw, NULL);
    }

    // Wait for all threads to finish
    for (int i = 0; i < NUM_THREADS; i++) {
        pthread_join(threads[i], NULL);
    }

    // Destroy the mutex
    pthread_mutex_destroy(&balance_lock);

    printf("Final Balance: %d\n", balance);  // Expected output: Final Balance: 0
    return 0;
}
