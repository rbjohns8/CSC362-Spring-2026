#include <stdio.h>
#include <unistd.h>

int main() {
    pid_t pid = fork();
    
    if (pid < 0) {  // Error in fork()
        perror("Fork failed");
        return 1;
    }
    else if (pid == 0) {  // Child process
        printf("Child process with PID %d\n", getpid());
        printf("Child process with PPID %d\n", getppid());
        printf("Child process with pid %d\n", pid);


    }
    else {  // Parent process
        printf("Parent process with PID %d\n", getpid());
        printf("Parent process with pid %d\n", pid);
    }
    
    return 0;
}
