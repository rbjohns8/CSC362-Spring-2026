#include <stdio.h>

int main() {
    int arr[] = {1, 2, 3};
    int *ptr = arr;
    ptr++;  // Now points to arr[1]
    ptr++;
    printf("Element: %d\n", *ptr);

    return 0;
}

