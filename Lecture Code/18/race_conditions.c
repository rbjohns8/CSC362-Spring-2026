#include <stdio.h>
#include <pthread.h>

int counter = 0;

void* increment_counter(void* arg) {
    for (int i = 0; i < 100000; i++) {
        counter++;  // Not thread-safe; race condition here
    }
    return NULL;
}

int main() {
    pthread_t t1, t2;

    pthread_create(&t1, NULL, increment_counter, NULL);
    pthread_create(&t2, NULL, increment_counter, NULL);

    pthread_join(t1, NULL);
    pthread_join(t2, NULL);

    printf("Final Counter Value: %d\n", counter);  // Result is unpredictable
    return 0;
}
