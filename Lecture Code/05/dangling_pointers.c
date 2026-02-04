#include <stdio.h>
#include <stdlib.h>  // Required for malloc and free

int main() {
    int n = 5;
    // Dynamic allocation of an array of 'n' integers using malloc
    int *arr = (int *)malloc(n * sizeof(int));

    // Check if the memory allocation was successful
    if (arr == NULL) {
        printf("Memory allocation failed\n");
        return 1;  // Exit the program if allocation failed
    }

    // Populating the dynamically allocated array with values
    for (int i = 0; i < n; i++) {
        arr[i] = i + 1;
    }

    // Printing the elements of the dynamically allocated array
    printf("Dynamically Allocated Array:\n");
    for (int i = 0; i < n; i++) {
        printf("arr[%d] = %d\n", i, arr[i]);
    }

    // Freeing the dynamically allocated memory
    free(arr);  // Deallocates the memory block pointed to by 'arr'

    // After freeing, 'arr' becomes a dangling pointer
    // For safety, set it to NULL to avoid accidental use
    arr = NULL;

    // Demonstrating that 'arr' is now NULL
    if (arr == NULL) {
        printf("Memory has been freed and the pointer is now NULL.\n");
    } else {
        printf("The pointer is not NULL. Be cautious when using it.\n");
    }

    return 0;
}
