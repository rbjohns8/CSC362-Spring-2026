#include <stdio.h>

// Define MAX as 100
#define MAX 100  

// Undefine MAX before the function
#undef MAX  

void my_function() {
    // Now MAX is treated as a local variable
    int MAX = 50;  
    printf("MAX inside function: %d\n", MAX);
}

// Redefine MAX after the function
#define MAX 100

int main() {
    my_function();
    
    // Now the macro MAX is 100 again
    printf("MAX outside function: %d\n", MAX);

    return 0;
}





