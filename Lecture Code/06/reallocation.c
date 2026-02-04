#include <stdio.h>
#include <stdlib.h>  // Required for malloc, realloc, and free

int main() {
    int n = 5;  // Initial size of the array
    // Dynamic allocation of an array of 'n' integers using malloc
    int *arr = (int *)malloc(n * sizeof(int));

    // Check if the memory allocation was successful
    if (arr == NULL) {
        printf("Memory allocation failed\n");
        return 1;  // Exit the program if allocation failed
    }

    // Populating the initially allocated array with values
    for (int i = 0; i < n; i++) {
        arr[i] = i + 1;
    }

    // Printing the elements of the initially allocated array
    printf("Initially Allocated Array:\n");
    for (int i = 0; i < n; i++) {
        printf("arr[%d] = %d\n", i, arr[i]);
    }

    // Resizing the array to hold 10 integers using realloc
    int new_size = 10;
    arr = (int *)realloc(arr, new_size * sizeof(int));

    // Check if the memory reallocation was successful
    if (arr == NULL) {
        printf("Memory reallocation failed\n");
        return 1;  // Exit the program if reallocation failed
    }

    // Populating the additional space in the reallocated array
    for (int i = n; i < new_size; i++) {
        arr[i] = i + 1;
    }

    // Printing the elements of the reallocated array
    printf("Reallocated Array:\n");
    for (int i = 0; i < new_size; i++) {
        printf("arr[%d] = %d\n", i, arr[i]);
    }

    // Freeing the dynamically allocated memory
    free(arr);
    arr = NULL;  // Good practice: Set the pointer to NULL after freeing

    return 0;
}
