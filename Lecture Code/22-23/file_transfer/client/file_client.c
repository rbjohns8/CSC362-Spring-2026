#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <pthread.h>

#define PORT 9002
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

void send_file(const char *filename, int sock) {
    FILE *fp = fopen(filename, "r");
    if (!fp) {
        perror("File open failed");
        return;
    }

    char buffer[BUF_SIZE];

    // Send command: /file filename
    snprintf(buffer, BUF_SIZE, "/file %s", filename);
    send(sock, buffer, strlen(buffer), 0);
    usleep(100000); // Small delay to avoid merge with file data

    // Read and send the file in chunks
    while (!feof(fp)) {
        memset(buffer, 0, BUF_SIZE);
        size_t bytes_read = fread(buffer, 1, BUF_SIZE, fp);
        send(sock, buffer, bytes_read, 0);
    }

    fclose(fp);
    usleep(100000); // Small delay
    send(sock, "/done", 5, 0);
    printf("✅ File sent.\n");
}

int main() {
    int sock = 0;
    struct sockaddr_in serv_addr;
    char buffer[BUF_SIZE] = {0};

    sock = socket(AF_INET, SOCK_STREAM, 0);
    if (sock < 0) {
        printf("Socket creation error\n");
        return -1;
    }

    serv_addr.sin_family = AF_INET;
    serv_addr.sin_port = htons(PORT);
    inet_pton(AF_INET, "127.0.0.1", &serv_addr.sin_addr);

    if (connect(sock, (struct sockaddr *)&serv_addr, sizeof(serv_addr)) < 0) {
        printf("Connection Failed\n");
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
        buffer[strcspn(buffer, "\n")] = 0; // Remove newline

        if (strncmp(buffer, "/send ", 6) == 0) {
    // Don't send the command as a chat message
            send_file(buffer + 6, sock);  // buffer + 6 is the filename
        continue; // skip sending this line as a normal message
        } else {
            send(sock, buffer, strlen(buffer), 0);
        }


        if (strncmp(buffer, "exit", 4) == 0) {
            printf("Chat ended.\n");
            break;
        }
    }

    close(sock);
    return 0;
}
