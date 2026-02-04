#include <stdio.h>

void test(int arr[5]) {
    int len = sizeof(arr);
    printf("Len: %lu\n", len);
}

int main() {
    int arr[] = {10, 20, 30, 40, 50};
    int *ptr = arr;

    int length = sizeof(arr) / sizeof(arr[0]);  // Calculate the length of the array

    printf("length: %d\n", length);
    printf("sizeof(arr): %d\n", sizeof(arr));
    printf("sizeof(arr[0]): %d\n", sizeof(arr[0]));

    for (int i = 0; i < length; i++) {
        printf("Element: %d\n", *(ptr + i));  // Corrected pointer arithmetic
    }

    test(arr);

    return 0;
}



