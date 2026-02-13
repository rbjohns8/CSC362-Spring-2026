// main.c
#include <stdio.h>

// Declare the functions from foo.c and bar.c
void foo();
void bar();

int main() {
    printf("This is the main function.\n");
    foo();  // Call function from foo.c
    bar();  // Call function from bar.c
    return 0;
}
