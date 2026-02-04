#include <stdio.h>

int main()
{
    // Declare a variable
    int var = 100;

    //printf("Value of var: %d\n", var);
    //printf("Address of var: %p\n", &var);

    // Declare a pointer and assign address of the variable
    int *pointerVar = &var;

    printf("Value through pointer: %d\n", *pointerVar);
    printf("Address stored in pointer: %p\n", pointerVar);
    
}

