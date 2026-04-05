#include <stdio.h>
#include <pthread.h>
#include <stdbool.h>
#include <unistd.h>

volatile bool flag[2] = {false, false};
volatile int turn = 0;

void* thread1(void* arg) {
    for (int i = 0; i < 5; i++) {
        flag[0] = true;
        while (flag[1] && turn == 1); // Wait
        printf("Thread 1: Working...\n");
        sleep(1);
        turn = 1;
        flag[0] = false;
    }
    return NULL;
}

void* thread2(void* arg) {
    for (int i = 0; i < 5; i++) {
        flag[1] = true;
        while (flag[0] && turn == 0); // Wait
        printf("Thread 2: Working...\n");
        sleep(1);
        turn = 0;
        flag[1] = false;
    }
    return NULL;
}

int main() {
    pthread_t t1, t2;
    pthread_create(&t1, NULL, thread1, NULL);
    pthread_create(&t2, NULL, thread2, NULL);

    pthread_join(t1, NULL);
    pthread_join(t2, NULL);
    return 0;
}
