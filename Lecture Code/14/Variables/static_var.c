#include <stdio.h>

void count_calls() {
    static int call_count = 0;  // Static local variable, stored in data segment
    call_count++;
    printf("Function called %d times\n", call_count);
}

int main() {
    count_calls();
    count_calls();
    count_calls();
    return 0;
}
