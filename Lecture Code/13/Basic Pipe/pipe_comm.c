#include <stdio.h>
#include <unistd.h>
#include <string.h>

int main() {
    int pipefd[2];
    char buffer[100];

    if (pipe(pipefd) == -1) {
        perror("pipe");
        return 1;
    }

    if (fork() == 0) {  // Child process
        close(pipefd[1]);  // Close unused write end
        read(pipefd[0], buffer, sizeof(buffer));
        printf("Child received: %s\n", buffer);
        close(pipefd[0]);
    } else {  // Parent process
        close(pipefd[0]);  // Close unused read end
        write(pipefd[1], "Hello from parent", 17);
        close(pipefd[1]);
    }

    return 0;
}
