#include <stdio.h>

int main() {
    // Static allocation of an array of 5 integers
    int arr[5] = {1, 2, 3, 4, 5};  // The size and memory for the array is determined at compile-time

    // Printing the elements of the statically allocated array
    printf("Static Array:\n");
    for (int i = 0; i < 5; i++) {
        printf("arr[%d] = %d\n", i, arr[i]);
    }

    // The array 'arr' does not need to be freed because it is statically allocated
    return 0;
}




