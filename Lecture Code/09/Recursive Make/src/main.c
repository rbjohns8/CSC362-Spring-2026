// src/main.c
#include <stdio.h>
#include "util.h"

// Declare the function from the math library
void math_function();

int main() {
    printf("Calling a function from util.c\n");
    util_function();

    printf("Calling a function from math.c\n");
    math_function();
    return 0;
}
