// relocation_example1.c
#include <stdio.h>

int global_var = 10;  // Global variable with a relocatable address

void print_global() {
    printf("Global variable: %d\n", global_var);
}

int main() {
    print_global();  // Call function that accesses the global variable
    return 0;
}
