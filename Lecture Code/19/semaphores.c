#include <stdio.h>
#include <pthread.h>
#include <semaphore.h>
#include <fcntl.h> // For O_CREAT and O_EXCL
#include <unistd.h>

#define PARKING_SPOTS 5
#define SEM_NAME "/parking_lot" // Unique name for the semaphore

sem_t *parking_lot;

void* car(void* arg) {
    printf("Car %ld: Arriving...\n", (long)arg);
    sem_wait(parking_lot); // Wait for a free spot
    printf("Car %ld: Parked.\n", (long)arg);
    sleep(2); // Simulate parking duration
    printf("Car %ld: Leaving.\n", (long)arg);
    sem_post(parking_lot); // Free a spot
    return NULL;
}

int main() {
    pthread_t cars[10];

    // Create a named semaphore with 5 parking spots
    parking_lot = sem_open(SEM_NAME, O_CREAT | O_EXCL, 0644, PARKING_SPOTS);
    if (parking_lot == SEM_FAILED) {
        perror("sem_open failed");
        return 1;
    }

    for (long i = 0; i < 10; i++) {
        pthread_create(&cars[i], NULL, car, (void*)i);
    }

    for (int i = 0; i < 10; i++) {
        pthread_join(cars[i], NULL);
    }

    // Close and unlink the semaphore
    sem_close(parking_lot);
    sem_unlink(SEM_NAME);

    return 0;
}
