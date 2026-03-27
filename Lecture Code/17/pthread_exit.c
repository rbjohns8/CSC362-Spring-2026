#include <stdio.h>
#include <pthread.h>

void *thread_function(void *arg) {
    printf("Thread: Executing and exiting...\n");
    pthread_exit(NULL); // Terminates the thread
}

int main() {
    pthread_t thread_id;
    pthread_create(&thread_id, NULL, thread_function, NULL);

    // Wait for thread to finish
    pthread_join(thread_id, NULL);
    printf("Main: Thread has exited\n");
    return 0;
}
