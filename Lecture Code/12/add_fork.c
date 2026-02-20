#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h> // Added for wait()

int main() {
    int a = 5, b = 3;

    // Perform the same calculation in both parent and child
    int result = a * b;
    printf("Multiplication: %d * %d = %d\n", a, b, result);

    pid_t pid = fork(); // Fork the process

    if (pid == 0) {
        // Child process
        printf("Child Process continuing...\n");
        execlp("./add", "add", NULL); // Replace the child code with the addition program
        
        // These lines only run if execlp fails
        perror("exec failed");
        exit(1);
    } else if (pid > 0) {
        // Parent process
        printf("Parent Process waiting for child...\n");
        wait(NULL); // Wait for the child to finish
        printf("Parent Process: Child finished execution.\n");
    } else {
        // Fork failed
        perror("fork failed");
        exit(1);
    }

    return 0;
}
