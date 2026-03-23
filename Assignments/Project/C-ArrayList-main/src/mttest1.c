#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <pthread.h>

#include "alist.h"

// The global array list

alist global_list;

#define NTHREADS 5
#define AVGQSIZE 100
#define NOPS 1000000

/*
 * This function creates a large number of linked list add and remove
 * operations on a global, shared list, in order to stress-test
 * multi-threaded alist add and remove functions. The exact parameters
 * can be set with the constants above, and will run NOPS operations
 * (either add or remove), attempting to maintain an average list
 * length of AVGQSIZE, with NTHREADS concurrent threads performing
 * operations. The default parameters are to perform 1 million
 * operations in each thread, maintaining an average list length of
 * 100 per thread. All removes are done from the front of the list,
 * since that's where most of the contention for the alist struct will
 * happen.
 *
 * Valgrind note: If you want to use valgrind to test your
 * implementation for memory leaks (a good idea!), it would be too
 * slow to run 1 million operations. For valgrind testing, a good
 * setting would be to set NOPS to around 1000.
 */

void *thread(void *arg) {
    int my_task_count = 0;

    /* Perform the operations */
    for (int i=0; i<NOPS; i++) {
        double prob = drand48();
        int dir = (my_task_count<AVGQSIZE)?+1:-1;
        int diff = abs(my_task_count-AVGQSIZE);

        /* You can move away from the average, but the probability decreases
         * the further the size is from the desired average. */
        if (diff < AVGQSIZE/10) {
            if (prob <= 0.5)
                dir = -dir;
        } else if (diff < AVGQSIZE/2) {
            if (prob <= 0.15)
                dir = -dir;
        } else if (prob <= 0.05) {
            dir = -dir;
        }

        /* Do the actual operation. */
        if (dir > 0) {
            alist_add(&global_list, strdup("Test"));
            my_task_count++;
        } else {
            alist_remove(&global_list, 0);
            my_task_count--;
        }
    }

    return NULL;
}

/************************************************************************
 * main just sets up two threads to concurrently run the "thread"
 * function.
 */
int main(int argc, char *argv[]) {
    pthread_t pt[NTHREADS];

    /* Initialize the list to empty */
    alist_init(&global_list, free);

    for (int i=0; i<NTHREADS; i++)
        pthread_create(&pt[i], NULL, thread, NULL);

    for (int i=0; i<NTHREADS; i++)
        pthread_join(pt[i], NULL);

    /* Empty out and free the space for the queues. */
    alist_destroy(&global_list);

    return 0;
}
