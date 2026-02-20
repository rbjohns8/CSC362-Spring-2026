#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>

int main() {
    pid_t pid = fork();  // Create a child process

    if (pid < 0) {  // If fork fails
        perror("Fork failed");
        exit(EXIT_FAILURE);
    }

    if (pid == 0) {  // Child process
        // Compute area of a square (side = 5)
        int side = 5;
        int area_square = side * side;
        printf("Child process (PID: %d) computes area of square: %d\n", getpid(), area_square);

        // Flush the output to make sure it's printed before exec
        fflush(stdout);

        // Simulate some work by sleeping
        sleep(2);

        printf("Child process now replacing its image to compute area of triangle...\n");

        // Flush again to ensure output before exec
        fflush(stdout);

        // Replace child process with a program that computes the area of a triangle
        execl("/bin/echo", "echo", "Area of triangle (base=4, height=3):", "6", (char *)NULL);

        // If exec fails, we print an error message
        perror("Exec failed");
        exit(EXIT_FAILURE);
    } else {  // Parent process
        // Parent waits for the child to finish
        wait(NULL);
        printf("Parent process (PID: %d) finished.\n", getpid());
    }

    return 0;
}