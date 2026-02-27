#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int main() {
    pid_t pid = fork(); // Fork a child process
    
    if (pid < 0) {
        // Fork failed
        perror("Fork failed");
        exit(1);
    } 
    else if (pid == 0) {
        // Child process
        printf("Child process started with PID: %d\n", getpid());
        printf("Child's parent PID before orphaning: %d\n", getppid());
        sleep(5); // Wait for the parent to exit
        printf("Child's parent PID after orphaning: %d\n", getppid());
        printf("Child process is now an orphan, adopted by init (PID 1)\n");
    } 
    else {
        // Parent process
        sleep(2);  // Ensure the parent is alive when the child prints the initial parent PID
        printf("Parent process (PID: %d) exiting...\n", getpid());
        exit(0);  // Parent exits, leaving the child orphaned
    }

    return 0;
}
