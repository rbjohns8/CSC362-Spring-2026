#include <stdio.h>
#include <stdlib.h>

int main() {
    // Step 1: Before allocating memory
    printf("Program started. Heap state before allocation.\n");
    printf("Press Enter to proceed with memory allocation...\n");
    getchar();  // Pause to allow checking heap state before allocation

    // Step 2: Allocate memory on the heap
    int *arr = (int *)malloc(1000000 * sizeof(int));  // Allocate memory for 1,000,000 integers (about 4 MB)
    if (!arr) {
        printf("Memory allocation failed\n");
        return 1;
    }
    
    printf("Memory allocated (4 MB for 1,000,000 ints). Heap state after allocation.\n");
    printf("Press Enter to proceed with memory deallocation...\n");
    getchar();  // Pause to allow checking heap state after allocation

    // Step 3: Free the allocated memory
    free(arr);
    printf("Memory deallocated. Heap state after deallocation.\n");
    printf("Press Enter to exit the program...\n");
    getchar();  // Pause to allow checking heap state after deallocation

    return 0;
}
