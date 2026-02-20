#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>

int main() {
    char *cmd[] = {"/bin/ls", NULL};  // Command to execute (ls)

    while (1) {
        printf("shell> ");  // Display prompt
        fflush(stdout);  // Ensure prompt is shown

        pid_t pid = fork();  // Fork a new process

        if (pid == 0) {  // Child process
            execvp(cmd[0], cmd);  // Replace child with command (ls)
            perror("exec failed");
            _exit(1);
        } else {  // Parent process
            wait(NULL);  // Wait for child to finish
        }
    }

    return 0;
}
