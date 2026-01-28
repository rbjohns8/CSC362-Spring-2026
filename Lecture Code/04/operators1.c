#include <stdio.h>

struct Point { int x, y; };

int main() {
    // 1. Subscript Operator []
    int arr[3] = {10, 20, 30};
    printf("Array element 1: %d\n", arr[1]); // Same as *(arr + 1)

    // 2. Structure Dereference (Arrow) ->
    struct Point p1 = {10, 20};
    struct Point *ptr = &p1;
    printf("Point X via arrow: %d\n", ptr->x);

    // 3. Structure Reference (Dot) .
    printf("Point Y via dot: %d\n", p1.y);

    // 4. Unary Plus/Minus +/-
    int val = 5;
    printf("Negated: %d\n", -val); // -5
    return 0;
}
