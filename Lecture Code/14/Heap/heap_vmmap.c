#include <stdio.h>
#include <stdlib.h>

int main() {
    int *arr = (int *)malloc(100 * sizeof(int)); // allocate memory on heap
    for (int i = 0; i < 100; i++) {
        arr[i] = i;
    }
    printf("Memory allocated and populated.\n");
    free(arr);  // deallocate
    getchar();  // pause to keep the program running
    return 0;
}
