#include <stdio.h>

#define MAX_AGE 120          // Maximum allowed age
#define MIN_AGE 0            // Minimum allowed age
#define GREETING "Hello, World!"  // A simple string constant

int main() {
    int age = 25;

    if (age > MIN_AGE && age < MAX_AGE) {
        printf("%s\n", GREETING);  // GREETING is replaced with "Hello, World!"
        printf("Your age is valid: %d\n", age);
    } else {
        printf("Age is not valid.\n");
    }

    return 0;
}





