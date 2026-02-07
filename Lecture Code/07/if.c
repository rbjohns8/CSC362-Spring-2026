#include <stdio.h>

#define DEBUG 0  // Set to 0 for production

int main() {
#if DEBUG
    printf("Debugging is enabled.\n");
#endif
    
    printf("Program is running.\n");
    return 0;
}


