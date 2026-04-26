#include <stdio.h>
#include <signal.h>
#include <unistd.h>
#include <openssl/sha.h>

#define ZBITS 30
#define INSIZE 16

/**************************************************************************
 * Search for an input to SHA256 that results in the first ZBITS bits of
 * the hash value being zero.
 */
int main(int argc, char *argv[]) {
    int found = 0;
    unsigned char tohash[INSIZE];
    unsigned char md[SHA256_DIGEST_LENGTH];

    for (int i=0; i<INSIZE; i++)
        tohash[i] = 0;

    while (!found) {
        SHA256(tohash, INSIZE, md);
        int bitsclear = 0;
        int j;
        for (j=0; j<SHA256_DIGEST_LENGTH && md[j]==0; j++) {
            bitsclear += 8;
        }
        if (j < SHA256_DIGEST_LENGTH) {
            for (int m=0x80; (md[j]&m) == 0; m >>= 1)
                bitsclear++;
        }

        if (bitsclear >= ZBITS) {
            break;
        } else {
            for (int j=0; j<INSIZE; j++) {
                if (++tohash[j] != 0) break;
            }
        }
    }

    printf("Input: ");
    for (int i=0; i<INSIZE; i++)
        printf(" %02x", tohash[i]);
    printf("\n");

    return 0;
}
