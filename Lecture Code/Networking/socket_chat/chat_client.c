#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <pthread.h>

#define PORT 9001
#define BUF_SIZE 1024

void *receive_messages(void *sock) {
    int server_sock = *(int *)sock;
    char buffer[BUF_SIZE];
    while (1) {
        memset(buffer, 0, BUF_SIZE);
        int valread = read(server_sock, buffer, BUF_SIZE);
        if (valread <= 0) break;

        if (strncmp(buffer, "exit", 4) == 0) {
            printf("\nServer ended the chat.\n");
            break;
        }

        printf("\nServer: %s", buffer);
        printf("\nYou: ");
        fflush(stdout);
    }
    return NULL;
}

int main() {
    int sock = 0;
    struct sockaddr_in serv_addr;
    char buffer[BUF_SIZE] = {0};

    sock = socket(AF_INET, SOCK_STREAM, 0);
    if (sock < 0) {
        printf("\nSocket creation error\n");
        return -1;
    }

    serv_addr.sin_family = AF_INET;
    serv_addr.sin_port = htons(PORT);

    // Connect to localhost (127.0.0.1)
    if (inet_pton(AF_INET, "127.0.0.1", &serv_addr.sin_addr) <= 0) {
        printf("\nInvalid address / Address not supported\n");
        return -1;
    }

    if (connect(sock, (struct sockaddr *)&serv_addr, sizeof(serv_addr)) < 0) {
        printf("\nConnection Failed\n");
        return -1;
    }

    printf("✅ Connected to server.\n");

    pthread_t recv_thread;
    pthread_create(&recv_thread, NULL, receive_messages, &sock);

    while (1) {
        printf("You: ");
        fflush(stdout);
        memset(buffer, 0, BUF_SIZE);
        fgets(buffer, BUF_SIZE, stdin);
        send(sock, buffer, strlen(buffer), 0);

        if (strncmp(buffer, "exit", 4) == 0) {
            printf("Chat ended.\n");
            break;
        }
    }

    close(sock);
    return 0;
}
