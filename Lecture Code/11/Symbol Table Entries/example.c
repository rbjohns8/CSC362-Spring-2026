#include <stdio.h>

int global_var = 42;

void print_message() {
    printf("Hello from function!\n");
}

int main() {
    int local_var = 10;
    print_message();
    return 0;
}
