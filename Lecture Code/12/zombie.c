#include <stdio.h>
#include <unistd.h>
#include <sys/wait.h>

int main() {
    pid_t pid = fork();  // Create a child process

    if (pid < 0) {
        perror("Fork failed");
        return 1;
    }

    if (pid == 0) {  // Child process
        printf("Child process terminating (PID: %d)\n", getpid());
        _exit(0);  // Child terminates immediately
    } else {  // Parent process
        printf("Parent process (PID: %d), child PID: %d\n", getpid(), pid);
        sleep(60);  // Simulate delay (child becomes zombie)
        printf("Parent process collecting child status...\n");
        wait(NULL);  // Collect child status, prevent zombie
    }

    return 0;
}
