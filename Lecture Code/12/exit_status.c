#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>

int main() {
    pid_t pid;
    int status;

    pid = fork();  // Create a child process

    if (pid < 0) {  // If fork fails
        perror("Fork failed");
        exit(EXIT_FAILURE);
    }

    if (pid == 0) {  // Child process
        // Simulate a situation where the child process exits with a custom status
        printf("Child process (PID: %d) doing some work...\n", getpid());

        // Let's use a random exit status code based on a simple condition
        int exit_status = 0;
        if (getpid() % 2 == 0) {
            printf("Child process exiting with status 0 (success).\n");
            exit_status = 0;  // Success status
        } else {
            printf("Child process exiting with status 1 (failure).\n");
            exit_status = 1;  // Failure status
        }

        _exit(exit_status);  // Child process terminates
    } else {  // Parent process
        // Parent waits for the child to terminate and captures its exit status
        wait(&status);

        if (WIFEXITED(status)) {  // Check if the child terminated normally
            printf("Parent: Child exited with status %d\n", WEXITSTATUS(status));
        } else if (WIFSIGNALED(status)) {  // Check if the child was terminated by a signal
            printf("Parent: Child was terminated by signal %d\n", WTERMSIG(status));
        }
    }

    return 0;
}
