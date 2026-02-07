#include <stdio.h>

#define DOUBLE_SUM(x, y) 2 * (x + y)  // Parameterized macro without parentheses

int main() {
    int a = 3, b = 4;

    // Expected: 2 * (a + b) = 2 * (3 + 4) = 14
    // Actual: (2 * 3) + 4 = 10 due to lack of parentheses
    printf("Result: %d\n", DOUBLE_SUM(a, b));

    return 0;
}



