#include <stdio.h>

int main() {
    // 1. Decrement --
    int count = 10;
    count--; 
    printf("Count: %d\n", count); // 9

    // 2. sizeof operator
    printf("Size of an int: %zu bytes\n", sizeof(int));

    // 3. Arithmetic Binary Operators & Pointer Arithmetic
    int list[5] = {10, 20, 30, 40, 50};
    int *ptr = list; // Points to list[0]
    
    // Pointer + Integer
    int *next = ptr + 2; 
    printf("Arithmetic: 5 + 2 = %d\n", 5 + 2);
    printf("Pointer addition: %d\n", *next); // Prints 30
    
    return 0;
}
