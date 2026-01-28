#include <stdio.h>

int main() {
    // 1. Dereference *a
    int num = 100;
    int *p = &num;
    printf("Value at p: %d\n", *p); // Accesses the memory address

    // 2. Address-of &a
    printf("Address of num: %p\n", (void*)&num);

    // 3. Increment ++ (Prefix vs Postfix)
    int a = 0;
    printf("Prefix ++a: %d\n", ++a); // Increments first, then returns (1)
    
    a = 0;
    printf("Postfix a++: %d\n", a++); // Returns first (0), then increments
    return 0;
}
