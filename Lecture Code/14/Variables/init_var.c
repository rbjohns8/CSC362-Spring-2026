#include <stdio.h>

int global_initialized = 100;  // Stored in data segment

int main() {
    int local_initialized = 10;  // Stored in stack segment
    printf("Global: %d, Local: %d\n", global_initialized, local_initialized);
    return 0;
}
