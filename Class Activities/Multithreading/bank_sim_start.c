#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <time.h>

#define NUM_ACCOUNTS 10
#define NUM_THREADS 5
#define TRANSACTIONS 100000

typedef struct {
    int balance;
    // TODO: Add a mutex here to protect this account
} Account;

Account bank[NUM_ACCOUNTS];

void* transfer_funds(void* arg) {
    int thread_id = *(int*)arg;
    
    for (int i = 0; i < TRANSACTIONS; i++) {
        int from = rand() % NUM_ACCOUNTS;
        int to = rand() % NUM_ACCOUNTS;
        while (to == from) to = rand() % NUM_ACCOUNTS;

        int amount = 10;

        /* * TODO: Implement the transfer safely.
         * 1. Acquire locks for both 'from' and 'to' accounts.
         * 2. Check if 'from' has enough balance.
         * 3. Perform the subtraction and addition.
         * 4. Release both locks.
         * * HINT: If your code hangs, you likely have a deadlock. 
         * Refer to Lecture 20's "Lock Ordering" strategy to fix it!
         */
        
        if (bank[from].balance >= amount) {
            bank[from].balance -= amount;
            bank[to].balance += amount;
        }
    }
    return NULL;
}

int main() {
    srand(time(NULL));
    pthread_t threads[NUM_THREADS];
    int thread_ids[NUM_THREADS];

    // Initialize accounts
    for (int i = 0; i < NUM_ACCOUNTS; i++) {
        bank[i].balance = 1000;
        // TODO: Initialize your mutexes here
    }

    printf("Starting simulation with %d accounts...\n", NUM_ACCOUNTS);

    for (int i = 0; i < NUM_THREADS; i++) {
        thread_ids[i] = i;
        pthread_create(&threads[i], NULL, transfer_funds, &thread_ids[i]);
    }

    for (int i = 0; i < NUM_THREADS; i++) {
        pthread_join(threads[i], NULL);
    }

    // Validation
    int total_wealth = 0;
    for (int i = 0; i < NUM_ACCOUNTS; i++) {
        total_wealth += bank[i].balance;
    }

    printf("Final Total Wealth: %d\n", total_wealth);
    printf("Expected Total Wealth: %d\n", NUM_ACCOUNTS * 1000);
    
    return 0;
}
