#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

void *thread_function(void *arg) {
    int *num = (int *)arg;
    printf("Thread: Received number %d\n", *num);
    pthread_exit(NULL); // Terminates the thread
}

int main() {
    pthread_t thread_id; // Thread identifier
    int number = 5;

    // Create a new thread
    if (pthread_create(&thread_id, NULL, thread_function, &number) != 0) {
        perror("Failed to create thread");
        return 1;
    }

    // Wait for the thread to complete
    if (pthread_join(thread_id, NULL) != 0) {
        perror("Failed to join thread");
        return 1;
    }

    printf("Main: Thread has completed execution\n");
    return 0;
}
