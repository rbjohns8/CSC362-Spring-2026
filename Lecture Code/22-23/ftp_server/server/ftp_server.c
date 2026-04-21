#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <dirent.h>
#include <arpa/inet.h>
#include <sys/socket.h>

#define PORT 8080
#define BUF_SIZE 1024

void handle_client(int client_sock) {
    char buffer[BUF_SIZE];
    while (1) {
        memset(buffer, 0, BUF_SIZE);
        int bytes_received = recv(client_sock, buffer, BUF_SIZE, 0);
        if (bytes_received <= 0) break;

        buffer[strcspn(buffer, "\n")] = 0;

        if (strncmp(buffer, "LIST", 4) == 0) {
            DIR *d;
            struct dirent *dir;
            d = opendir(".");
            if (d) {
                while ((dir = readdir(d)) != NULL) {
                    if (dir->d_type == DT_REG) {
                        send(client_sock, dir->d_name, strlen(dir->d_name), 0);
                        send(client_sock, "\n", 1, 0);
                    }
                }
                closedir(d);
            }
        } else if (strncmp(buffer, "GET ", 4) == 0) {
            char *filename = buffer + 4;
            FILE *fp = fopen(filename, "rb");
            if (fp == NULL) {
                send(client_sock, "File not found\n", 15, 0);
            } else {
                while (!feof(fp)) {
                    int n = fread(buffer, 1, BUF_SIZE, fp);
                    if (n > 0) send(client_sock, buffer, n, 0);
                }
                fclose(fp);
            }
        } else if (strncmp(buffer, "PUT ", 4) == 0) {
            char *filename = buffer + 4;
            FILE *fp = fopen(filename, "wb");
            if (fp == NULL) {
                send(client_sock, "Failed to create file\n", 22, 0);
                continue;
            }
            while ((bytes_received = recv(client_sock, buffer, BUF_SIZE, 0)) > 0) {
                fwrite(buffer, 1, bytes_received, fp);
                if (bytes_received < BUF_SIZE) break;
            }
            fclose(fp);
        } else if (strncmp(buffer, "QUIT", 4) == 0) {
            break;
        } else {
            send(client_sock, "Unknown command\n", 16, 0);
        }
    }
    close(client_sock);
}

int main() {
    int server_fd, client_sock;
    struct sockaddr_in address;
    socklen_t addr_len = sizeof(address);

    server_fd = socket(AF_INET, SOCK_STREAM, 0);
    if (server_fd == 0) {
        perror("Socket failed");
        exit(EXIT_FAILURE);
    }

    address.sin_family = AF_INET;
    address.sin_addr.s_addr = INADDR_ANY;
    address.sin_port = htons(PORT);

    bind(server_fd, (struct sockaddr *)&address, sizeof(address));
    listen(server_fd, 3);

    printf("FTP-like Server started on port %d...\n", PORT);

    while ((client_sock = accept(server_fd, (struct sockaddr *)&address, &addr_len)) >= 0) {
        printf("Client connected.\n");
        handle_client(client_sock);
        printf("Client disconnected.\n");
    }

    close(server_fd);
    return 0;
}
