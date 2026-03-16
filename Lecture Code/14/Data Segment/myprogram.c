#include <stdio.h>

// Global variables
int global_initialized = 42;  // Initialized data segment
int global_uninitialized;     // Uninitialized data segment (BSS)

// Function with static local variables
void static_demo() {
    static int static_initialized = 10;  // Data segment (initialized)
    static int static_uninitialized;     // Data segment (uninitialized / BSS)
    
    // Modify the static variables
    static_initialized++;
    static_uninitialized++;
    
    printf("Static Initialized: %d, Static Uninitialized: %d\n", static_initialized, static_uninitialized);
}

int main() {
    printf("Global Initialized: %d, Global Uninitialized: %d\n", global_initialized, global_uninitialized);
    
    // Call static_demo function multiple times
    static_demo();
    static_demo();  // Static variables retain their values between calls
    
    return 0;
}
