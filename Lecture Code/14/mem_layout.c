#include <stdio.h>
#include <stdlib.h>

int global_var = 10;  // Initialized data segment
int uninitialized_var; // BSS segment

void memory_layout_demo() {
    int local_var = 5;  // Stack segment
    int *dynamic_var = (int*) malloc(sizeof(int)); // Heap segment
    *dynamic_var = 50;

    printf("Address of function (text segment): %p\n", (void*) memory_layout_demo);
    printf("Address of global initialized variable: %p\n", (void*) &global_var);
    printf("Address of global uninitialized variable (BSS): %p\n", (void*) &uninitialized_var);
    printf("Address of local variable (stack): %p\n", (void*) &local_var);
    printf("Address of dynamically allocated variable (heap): %p\n", (void*) dynamic_var);

    free(dynamic_var); // Free heap memory
}

int main() {
    memory_layout_demo();
    return 0;
}
