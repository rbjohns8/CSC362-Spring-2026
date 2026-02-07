#include <stdio.h>

#define PI 3.14159
#define SQUARE(x) ((x) * (x))

int main() {

    printf("The value of PI is: %f\n", PI);

    int result = SQUARE(5);  
    printf("The square of 5 is: %d\n", result);

    return 0;
}




