#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <netinet/in.h>
#include <sys/socket.h>
#include <sys/time.h>

#define DNS_SERVER "8.8.8.8"
#define DNS_PORT 53
#define BUF_SIZE 512

struct DNSHeader {
    unsigned short id;
    unsigned short flags;
    unsigned short qdcount;
    unsigned short ancount;
    unsigned short nscount;
    unsigned short arcount;
};

void build_dns_query(unsigned char *buf, const char *host, int *query_len) {
    struct DNSHeader *dns = (struct DNSHeader *)buf;
    dns->id = htons(0x4321);            // Transaction ID
    dns->flags = htons(0x0100);         // Standard query with recursion
    dns->qdcount = htons(1);            // One question
    dns->ancount = 0;
    dns->nscount = 0;
    dns->arcount = 0;

    printf("[DNS Builder] Encoding domain: %s\n", host);

    unsigned char *qname = buf + sizeof(struct DNSHeader);
    const char *pos = host;

    while (*pos) {
        const char *dot = strchr(pos, '.');
        int len = dot ? dot - pos : strlen(pos);
        *qname++ = len;
        memcpy(qname, pos, len);
        qname += len;
        if (!dot) break;
        pos = dot + 1;
    }
    *qname++ = 0; // Null terminator

    *((unsigned short *)qname) = htons(1); // Type A
    qname += 2;
    *((unsigned short *)qname) = htons(1); // Class IN
    qname += 2;

    *query_len = qname - buf;
}

void parse_dns_response(unsigned char *buf) {
    struct DNSHeader *dns = (struct DNSHeader *)buf;
    unsigned char *reader = buf + sizeof(struct DNSHeader);

    // Skip over the question section
    while (*reader != 0) reader += (*reader) + 1;
    reader += 5; // null + qtype (2) + qclass (2)

    printf("\n[DNS Response] ID: 0x%x | Answers: %d\n",
           ntohs(dns->id), ntohs(dns->ancount));

    for (int i = 0; i < ntohs(dns->ancount); i++) {
        reader += 2; // name (compressed)
        unsigned short type = ntohs(*(unsigned short *)reader); reader += 2;
        reader += 2; // class
        reader += 4; // TTL
        unsigned short rdlen = ntohs(*(unsigned short *)reader); reader += 2;

        if (type == 1 && rdlen == 4) {
            printf("→ IPv4 Address Found: %d.%d.%d.%d\n",
                   reader[0], reader[1], reader[2], reader[3]);
        } else {
            printf("→ Skipped non-A record (type %d)\n", type);
        }

        reader += rdlen;
    }
}

int main(int argc, char *argv[]) {
    const char *hostname = argc > 1 ? argv[1] : "www.google.com";

    printf("┌────────────────────────────────────────────┐\n");
    printf("│   Manual DNS Resolver: %s\n", hostname);
    printf("└────────────────────────────────────────────┘\n");

    int sock = socket(AF_INET, SOCK_DGRAM, IPPROTO_UDP);
    if (sock < 0) {
        perror("Socket creation failed");
        return 1;
    }

    // Set receive timeout (3 seconds)
    struct timeval timeout = {3, 0};
    setsockopt(sock, SOL_SOCKET, SO_RCVTIMEO, &timeout, sizeof(timeout));

    struct sockaddr_in dest;
    dest.sin_family = AF_INET;
    dest.sin_port = htons(DNS_PORT);
    inet_pton(AF_INET, DNS_SERVER, &dest.sin_addr);

    unsigned char buf[BUF_SIZE];
    int query_len;
    build_dns_query(buf, hostname, &query_len);

    printf("\n[Sending DNS Query to %s:%d]\n", DNS_SERVER, DNS_PORT);
    if (sendto(sock, buf, query_len, 0, (struct sockaddr *)&dest, sizeof(dest)) < 0) {
        perror("sendto failed");
        close(sock);
        return 1;
    }

    socklen_t slen = sizeof(dest);
    int resp_len = recvfrom(sock, buf, BUF_SIZE, 0, (struct sockaddr *)&dest, &slen);
    if (resp_len < 0) {
        perror("recvfrom timeout or error");
        close(sock);
        return 1;
    }

    parse_dns_response(buf);
    close(sock);
    return 0;
}
