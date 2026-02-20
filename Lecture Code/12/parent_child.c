#include <stdio.h>
#include <unistd.h>

int main() {
    int shared_var = 42;  // Shared data before fork

    pid_t pid = fork();  // Create child process

    if (pid < 0) {
        perror("Fork failed");
        return 1;
    }

    if (pid == 0) {  // Child process
        //printf("Child Process - PID: %d, PPID: %d, shared_var: %d\n", getpid(), getppid(), shared_var);
        //shared_var = 100;  // Modify variable in child process
        //printf("Child modified shared_var to %d\n", shared_var);
        printf("Child process pid value: %d\n", pid);
        printf("Child process ppid value: %d\n", getppid());
    } else {  // Parent process
        //printf("Parent Process - PID: %d, Child PID: %d, shared_var: %d\n", getpid(), pid, shared_var);
        //sleep(1);  // Sleep to let child run first
        //printf("Parent sees shared_var as %d\n", shared_var);  // Parent's copy is unchanged
        printf("Parent process pid value: %d\n", pid);
        printf("Parent process pid value: %d\n", getpid());
    }

    return 0;
}
