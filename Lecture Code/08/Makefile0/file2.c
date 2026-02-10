#include <stdio.h>
#include "file1.h"

//extern int globalVar;  // Declare the global variable defined in file1.c
//void printGlobal();    // Declare the function defined in file1.c

int main() {
    printGlobal();  // Call the function that uses the global variable
    return 0;
}
