#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int main() {
    // Instruction 1 and 2: Executed before fork
    int x = 10;  // Instruction 1
    int y = 20;  // Instruction 2

    pid_t pid = fork();  // Fork the process

    x = 100; // Instruction 3
    y = 200; // Instruction 4

    if (pid == 0) {
        // Child process inherits instruction 3 and 4
        // Uses exec to replace 3 and 4 with instructions in a new file so will not perform Insturction 3 and 4
        execlp("./new_image", "new_image", NULL);
        perror("exec failed");
        exit(1);
    } else if (pid > 0) {
        // Parent process
        wait(NULL);  // Wait for the child to finish
        printf("Parent Process: x = %d, y = %d\n", x, y);  // Outputs modified values for parent
    } else {
        perror("fork failed");
        exit(1);
    }

    return 0;
}


