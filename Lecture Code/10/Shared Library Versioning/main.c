#include <stdio.h>

// Declare the function from the shared library
void add(int a, int b);

int main() {
    add(5, 3); // Call the add function
    return 0;
}
