#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>  // For sleep()

int main() {
    int n = 5;
    int *arr = (int *)malloc(n * sizeof(int));

    if (!arr) {
        printf("Memory allocation failed\n");
        return 1;
    }

    for (int i = 0; i < n; i++) {
        arr[i] = i + 1;
    }

    for (int i = 0; i < n; i++) {
        printf("%d ", arr[i]);
    }
    printf("\n");

    printf("Memory allocated, check with `top`, `ps`, or `vmmap`.\n");
    sleep(100); // Pause for inspection

    free(arr);
    return 0;
}
