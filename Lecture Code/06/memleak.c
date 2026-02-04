#include <stdio.h>
#include <stdlib.h>
#include <unistd.h> // For sleep()

int main() {
    while (1) {
        int *leak = (int *)malloc(1024 * 1024); // Allocate 1MB of memory
        if (!leak) {
            printf("Memory allocation failed!\n");
            return 1;
        }
        printf("Allocated 1MB. Check memory usage!\n");
        sleep(1); // Slow down the leak for observation
    }
    return 0;
}
