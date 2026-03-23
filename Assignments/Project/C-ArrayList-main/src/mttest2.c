#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <pthread.h>

#include "alist.h"

#define NOPS 1000000

// The global array list

alist global_list;

/*
 * This driver has two threads - one just adds an item and
 * removes it, so the list size bounces back between 1 and 0.
 * The other thread just repeatedly uses get for item 0.
 */
void *thread_modifier(void *arg) {
    /* Perform the operations */
    for (int i=0; i<NOPS; i++) {
        alist_add(&global_list, strdup("Test"));
        alist_remove(&global_list, 0);
    }

    return NULL;
}

void *thread_checker(void *arg) {
    int counter = 0;
    for (int i=0; i<2*NOPS; i++) {
        char *res = alist_get(&global_list, 0);
        if (res == NULL) counter++;
    }

    printf("List was empty %d out of %d checks.\n", counter, 2*NOPS);
    return NULL;
}

/************************************************************************
 * main just sets up two threads to concurrently run the "thread"
 * function.
 */
int main(int argc, char *argv[]) {
    pthread_t pt1, pt2;

    /* Initialize the list to empty */
    alist_init(&global_list, free);

    pthread_create(&pt1, NULL, thread_modifier, NULL);
    pthread_create(&pt2, NULL, thread_checker, NULL);

    pthread_join(pt1, NULL);
    pthread_join(pt2, NULL);

    /* Empty out and free the space for the queues. */
    alist_destroy(&global_list);

    return 0;
}
