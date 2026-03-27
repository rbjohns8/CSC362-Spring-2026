#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <unistd.h>

void *thread_function(void *arg) {
    printf("Thread: Starting execution\n");
    for (int i = 0; i < 5; i++) {
        printf("Thread: Running... %d\n", i + 1);
        sleep(1); // Simulate work
    }
    pthread_exit(NULL);
}

int main() {
    pthread_t thread_id;
    pthread_create(&thread_id, NULL, thread_function, NULL);

    // Let thread run for 2 seconds, then cancel
    sleep(2);
    pthread_cancel(thread_id);
    printf("Main: Requested thread cancellation\n");

    // Ensure thread has terminated
    pthread_join(thread_id, NULL);
    printf("Main: Thread has been canceled\n");
    return 0;
}
