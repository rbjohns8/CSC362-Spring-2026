#include <stdio.h>
#include <stdlib.h>

int main() {
    // Allocate memory dynamically for an integer
    int *ptr = (int *)malloc(sizeof(int));

    if (ptr == NULL) {
        printf("Memory allocation failed\n");
        return 1;
    }

    // Assign a value to the allocated memory
    *ptr = 42;
    printf("Value at ptr: %d\n", *ptr);

    // Free the allocated memory
    free(ptr);

    // Attempting to free the same memory again 
    // - this causes a double free bug
    free(ptr);

    return 0;
}


