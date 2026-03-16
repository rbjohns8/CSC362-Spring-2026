#include <stdio.h>
#include <unistd.h>

#define NUM_CHILDREN 3

int main() {
    int i;

    printf("I'm the original process: PID=%d\n", getpid());
    fflush(stdout);

    for (i = 0; i < NUM_CHILDREN; i++) {
        if (fork() == 0) {
            printf("I'm a new child process! PID=%d\n", getpid());
            fflush(stdout);
        }
    }

    return 0;
}
