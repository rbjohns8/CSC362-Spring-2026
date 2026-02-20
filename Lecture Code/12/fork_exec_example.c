#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>

long factorial(int n) {
    if (n == 0 || n == 1) return 1;
    return n * factorial(n - 1);
}

int main() {
    pid_t pid;
    int status;
    
    int number = 5;  // We will calculate the factorial of this number

    pid = fork();  // Create a child process

    if (pid < 0) {  // If fork fails
        perror("Fork failed");
        exit(EXIT_FAILURE);
    }

    if (pid == 0) {  // Child process
        // Child computes factorial of a number
        long result = factorial(number);
        printf("Child process (PID: %d) computed factorial of %d: %ld\n", getpid(), number, result);

        // Sleep to give you time to observe the child process before exec()
        printf("Child process: Sleeping for 30 seconds before exec(). Observe the process using `ps`...\n");
        sleep(30);  // Sleep to give you time to run `ps` and observe the process
        
        printf("Child process: Now replacing itself with /bin/echo...\n");

        // Replace current process with 'echo' command using exec
        execl("/bin/sh", "sh", "-c", "echo 'Child after exec with same PID'; sleep 60", (char *)NULL);

        // If exec fails
        perror("Exec failed");
        exit(EXIT_FAILURE);
    } else {  // Parent process
        // Parent process information
        printf("Parent process (PID: %d) is running. Child PID is: %d\n", getpid(), pid);
        
        // Sleep to give you time to observe the parent and child processes
        printf("Parent process: Sleeping for 30 seconds. Observe both parent and child using `ps`...\n");
        sleep(30);  // Give time to observe parent and child processes

        // Wait for the child to terminate
        wait(&status);

        // Print message after child terminates
        printf("Parent process: Child process (PID: %d) terminated. Now you can check again using `ps`...\n", pid);

        if (WIFEXITED(status)) {
            printf("Child exited with status %d\n", WEXITSTATUS(status));
        }
    }

    return 0;
}
