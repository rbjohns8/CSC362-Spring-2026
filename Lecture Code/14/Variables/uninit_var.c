#include <stdio.h>

int global_uninitialized;  // Stored in BSS segment, automatically initialized to 0

int main() {
    int local_uninitialized;  // Stored in stack, contains garbage value
    printf("Global uninitialized: %d, Local uninitialized: %d\n", global_uninitialized, local_uninitialized);
    return 0;
}
