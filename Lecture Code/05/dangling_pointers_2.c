#include <stdio.h>
#include <stdlib.h>

int main() {
    // Allocate memory dynamically
    int *ptr = (int *)malloc(sizeof(int));
    *ptr = 42;

    // Print the value stored at the allocated memory
    printf("Before free (ptr value): %d\n", *ptr);
    printf("Before free (ptr address): %p\n", ptr);

    // Free the allocated memory
    free(ptr);

    // ptr is now a dangling pointer
    // Accessing it causes undefined behavior
    //printf("After free (dangling pointer value): %d\n", *ptr); // Undefined behavior
    //printf("After free (dangling pointer address): %p\n", ptr); // Undefined behavior

    // Good practice: Set pointer to NULL after freeing
    ptr = NULL;

    //occurs when a program tries to access an area of memory that it is not allowed to
    printf("Dereference a null or invalid pointer.: %d\n", *ptr);

    return 0;
}