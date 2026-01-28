#include <stdio.h>

int main() {
    // 1. Left Shift <<
    // Always introduces zeros on the right
    unsigned int x = 5; // Binary: 0000 0101
    printf("5 << 1 = %u\n", x << 1); // 10 (Binary: 0000 1010)

    // 2. Right Shift >> (Unsigned)
    // Always introduces zeros on the left
    unsigned int u = 8; // Binary: 0000 1000
    printf("Unsigned 8 >> 1 = %u\n", u >> 1); // 4 (Binary: 0000 0100)

    // 3. Right Shift >> (Signed)
    // Sign-extension: if the number is negative (sign bit set), 
    // it fills with 1s to preserve the sign.
    signed int s = -8; 
    printf("Signed -8 >> 1 = %d\n", s >> 1); // -4
    
    return 0;
}
