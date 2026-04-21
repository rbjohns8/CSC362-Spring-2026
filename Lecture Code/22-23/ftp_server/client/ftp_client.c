#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>

#define PORT 8080
#define BUF_SIZE 1024

int main() {
    int sock = 0;
    struct sockaddr_in serv_addr;
    char buffer[BUF_SIZE] = {0};

    sock = socket(AF_INET, SOCK_STREAM, 0);
    serv_addr.sin_family = AF_INET;
    serv_addr.sin_port = htons(PORT);
    inet_pton(AF_INET, "127.0.0.1", &serv_addr.sin_addr);

    connect(sock, (struct sockaddr *)&serv_addr, sizeof(serv_addr));

    printf("Connected to server. Available commands: LIST, GET <file>, PUT <file>, QUIT\n");

    while (1) {
        printf("ftp> ");
        fgets(buffer, BUF_SIZE, stdin);
        buffer[strcspn(buffer, "\n")] = 0;
        send(sock, buffer, strlen(buffer), 0);

        if (strncmp(buffer, "GET ", 4) == 0) {
            FILE *fp = fopen(buffer + 4, "wb");
            if (fp) {
                int bytes_received;
                while ((bytes_received = recv(sock, buffer, BUF_SIZE, 0)) > 0) {
                    fwrite(buffer, 1, bytes_received, fp);
                    if (bytes_received < BUF_SIZE) break;
                }
                fclose(fp);
                printf("File received.\n");
            }
        } else if (strncmp(buffer, "PUT ", 4) == 0) {
            FILE *fp = fopen(buffer + 4, "rb");
            if (fp) {
                int n;
                while ((n = fread(buffer, 1, BUF_SIZE, fp)) > 0) {
                    send(sock, buffer, n, 0);
                }
                fclose(fp);
                printf("File sent.\n");
            }
        } else if (strncmp(buffer, "QUIT", 4) == 0) {
            break;
        } else {
            int n = recv(sock, buffer, BUF_SIZE, 0);
            if (n > 0) {
                buffer[n] = 0;
                printf("%s", buffer);
            }
        }
    }

    close(sock);
    return 0;
}
