#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>  // For sleep function

void func() {
    printf("This is a function call.\n");
}

int main() {
    int a = 5, b = 10;
    int c = a + b;  // Arithmetic instruction
    printf("Sum: %d\n", c);  // Text segment: system call to output data

    func();  // Function call

    printf("The program will now pause. Use 'pmap' to inspect memory.\n");
    sleep(60);  // Sleep for 60 seconds to give you enough time to run pmap
    
    return 0;
}
