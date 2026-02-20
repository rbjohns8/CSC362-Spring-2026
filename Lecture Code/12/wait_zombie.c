#include <stdio.h>
#include <sys/wait.h>
#include <unistd.h>

int main() {
    pid_t pid = fork();
    
    if (pid == 0) {  // Child process
        printf("Child process: PID %d\n", getpid());
        _exit(0);  // Exiting child process
    }
    else {  // Parent process
        printf("Parent process waiting for child %d\n", pid);
        wait(NULL);  // Waiting for child to terminate
        printf("Child process finished, parent resuming\n");
    }
    
    return 0;
}
