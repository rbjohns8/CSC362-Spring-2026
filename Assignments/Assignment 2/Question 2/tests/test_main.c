#include <stdio.h>
#include "../include/math_lib.h"

int main() {
    printf("tests: Running tests...\n");
    int result = multiply(2, 5);  // Call the multiply function from the lib
    printf("tests: Test result of multiply(2, 5) = %d\n", result);
    return 0;
}
