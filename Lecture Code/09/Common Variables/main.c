// main.c
#include <stdio.h>
#include "util.h"  // Include the header file for the util functions

int main() {
    printf("Calling a function from util.c\n");
    util_function();  // Call the function from util.c
    return 0;
}
