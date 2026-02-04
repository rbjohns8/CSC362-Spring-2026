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

    // Allocate memory dynamically for an array of 5 integers
    int *arr = (int *)malloc(5 * sizeof(int));

    if (arr == NULL) {
        printf("Memory allocation for array failed\n");
        free(ptr);  // Free the previously allocated memory before exiting
        return 1;
    }

    // Assign values to the array
    for (int i = 0; i < 5; i++) {
        arr[i] = i + 1;
    }

    // Print the values in the array
    printf("Array values: ");
    for (int i = 0; i < 5; i++) {
        printf("%d ", arr[i]);
    }
    printf("\n");

    // Free the allocated memory
    free(ptr);
    free(arr);

    return 0;
}
