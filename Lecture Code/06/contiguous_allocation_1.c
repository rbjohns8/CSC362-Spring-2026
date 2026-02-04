#include <stdio.h>
#include <stdlib.h>  // Required for calloc and free

int main() {
    int n = 5;  // Size of the array
    // Dynamic allocation of an array of 'n' integers using calloc
    int *arr = (int *)calloc(n, sizeof(int));  // Allocates memory for 'n' integers and initializes all elements to 0

    // Check if the memory allocation was successful
    if (arr == NULL) {
        printf("Memory allocation failed\n");
        return 1;  // Exit the program if allocation failed
    }

    // Printing the elements of the dynamically allocated array (initial values should be 0)
    printf("Dynamically Allocated Array using calloc (initially all zeros):\n");
    for (int i = 0; i < n; i++) {
        printf("arr[%d] = %d\n", i, arr[i]);
    }

    // Populating the array with values
    for (int i = 0; i < n; i++) {
        arr[i] = i + 1;
    }

    // Printing the elements of the array after populating
    printf("Array after populating with values:\n");
    for (int i = 0; i < n; i++) {
        printf("arr[%d] = %d\n", i, arr[i]);
    }

    // Freeing the dynamically allocated memory
    free(arr);
    arr = NULL;  // Good practice: Set the pointer to NULL after freeing

    return 0;
}
