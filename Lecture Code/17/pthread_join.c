#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

void *thread_function(void *arg) {
    int *num = (int *)arg;
    int *result = malloc(sizeof(int)); // Allocate memory for result
    *result = (*num) * 2;
    printf("Thread: Double of %d is %d\n", *num, *result);
    pthread_exit(result); // Return result
}

int main() {
    pthread_t thread_id;
    int number = 5;
    int *result;

    pthread_create(&thread_id, NULL, thread_function, &number);
    pthread_join(thread_id, (void **)&result); // Wait for thread and get result

    printf("Main: Thread result = %d\n", *result);
    free(result); // Free memory allocated in the thread
    return 0;
}
