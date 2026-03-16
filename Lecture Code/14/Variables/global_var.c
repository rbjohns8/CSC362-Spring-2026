#include <stdio.h>

int global_var = 10;  // Initialized global variable, stored in data segment
int uninitialized_global_var;  // Uninitialized global variable, stored in BSS

int main() {
    printf("Global var: %d\n", global_var);
    return 0;
}

