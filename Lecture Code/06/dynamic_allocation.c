#include <stdio.h>
#include <stdlib.h>  // Required for malloc and free

int main() {
    int n = 5;  // Size of the array
    // Dynamic allocation of an array of 'n' integers
    int *arr = (int *)malloc(n * sizeof(int));  // Allocates memory for 'n' integers

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
    free(arr);
    arr = NULL;  // Good practice: Set the pointer to NULL after freeing

    return 0;
}
