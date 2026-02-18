#include <stdio.h>

// Declare the functions from the static library
int add(int, int);
int multiply(int, int);
int string_length(const char *);

int main() {
    int a = 5, b = 3;
    printf("Addition of %d and %d: %d\n", a, b, add(a, b));
    printf("Multiplication of %d and %d: %d\n", a, b, multiply(a, b));

    const char *str = "Hello, world!";
    printf("Length of '%s': %d\n", str, string_length(str));

    return 0;
}
