#include <stdio.h>

// Function declarations for functions defined in the shared library
void add(int a, int b);
void subtract(int a, int b);

int main() {
    add(10, 5);         // Call function from shared library
    subtract(10, 5);    // Call another function from shared library
    return 0;
}
