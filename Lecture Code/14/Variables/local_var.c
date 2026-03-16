#include <stdio.h>

void foo() {
    int local_var = 5;  // Local variable, stored in the stack segment
    printf("Local var: %d\n", local_var);
}

int main() {
    foo();
    return 0;
}
