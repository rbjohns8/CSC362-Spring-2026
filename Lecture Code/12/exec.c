#include <stdio.h>
#include <unistd.h>
#include <sys/wait.h>  // Include this for wait()

int main() {
    pid_t pid = fork();
    
    if (pid == 0) {  // Child process
        printf("Child: Executing `ls` command...\n");
        execl("/bin/ls", "ls", NULL);  // Replace child process with 'ls'
        // If exec fails
        perror("exec failed");
    }
    else {  // Parent process
        wait(NULL);  // Wait for child to finish
        printf("Child process finished\n");
    }
    
    return 0;
}
