#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <string.h>

int main() {
    char cmd[32];
    char input[32];

    while (1) {
        printf("shell> ");  // Display prompt
        fflush(stdout);  // Ensure prompt is shown
        
        scanf("%s", input);
        
        if ( strcmp(input, "done") == 0 ) {
          printf("The user entered 'done'.\n");
          break;
        }
        else if ( strcmp(input, "ls" ) == 0 ) {
          strcpy(cmd, "/bin/ls");
        }
        else if ( strcmp(input, "pwd") == 0 ) {
          strcpy(cmd, "/bin/pwd");
        }
        else {
          printf("Please enter a valid entry.\n");
          continue;
        }
        
        pid_t pid = fork();  // Fork a new process

        if (pid == 0) {  // Child process
            execl(cmd, cmd, NULL);  // Replace child with command (ls)
            perror("exec failed");
            _exit(1);
        } else {  // Parent process
            wait(NULL);  // Wait for child to finish
        }
    }

    return 0;
}