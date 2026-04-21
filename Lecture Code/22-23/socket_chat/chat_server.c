#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <pthread.h>

#define PORT 9001
#define BUF_SIZE 1024

void *receive_messages(void *sock) {
    int client_sock = *(int *)sock;
    char buffer[BUF_SIZE];
    while (1) {
        memset(buffer, 0, BUF_SIZE);
        int valread = read(client_sock, buffer, BUF_SIZE);
        if (valread <= 0) break;

        if (strncmp(buffer, "exit", 4) == 0) {
            printf("\nClient ended the chat.\n");
            break;
        }

        printf("\nClient: %s", buffer);
        printf("\nYou: ");
        fflush(stdout);
    }
    return NULL;
}

int main() {
    int server_fd, client_sock;
    struct sockaddr_in address;
    socklen_t addrlen = sizeof(address);
    char buffer[BUF_SIZE] = {0};

    server_fd = socket(AF_INET, SOCK_STREAM, 0);
    if (server_fd == 0) {
        perror("Socket failed");
        exit(EXIT_FAILURE);
    }

    address.sin_family = AF_INET;
    address.sin_addr.s_addr = INADDR_ANY;
    address.sin_port = htons(PORT);

    bind(server_fd, (struct sockaddr *)&address, sizeof(address));
    listen(server_fd, 1);
    printf("🔌 Server listening on port %d...\n", PORT);

    client_sock = accept(server_fd, (struct sockaddr *)&address, &addrlen);
    printf("✅ Client connected.\n");

    pthread_t recv_thread;
    pthread_create(&recv_thread, NULL, receive_messages, &client_sock);

    while (1) {
        printf("You: ");
        fflush(stdout);
        memset(buffer, 0, BUF_SIZE);
        fgets(buffer, BUF_SIZE, stdin);
        send(client_sock, buffer, strlen(buffer), 0);

        if (strncmp(buffer, "exit", 4) == 0) {
            printf("Chat ended.\n");
            break;
        }
    }

    close(client_sock);
    close(server_fd);
    return 0;
}
