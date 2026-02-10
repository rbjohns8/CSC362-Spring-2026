#include <stdio.h>
#include "myheader.h"  // Include the header file for declarations

// Function definition (implementation)
void print_message() {
    printf("Hello from the print_message function!\n");
}

int main() {
    print_message();  // Use the function defined above
    printf("Max value is: %d\n", MAX_VALUE);  // Use the macro from the header file
    return 0;
}
