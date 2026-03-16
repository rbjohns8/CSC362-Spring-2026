#include <stdio.h>

int main(int argc, char *argv[]) {
    int i;
    
    printf("Number of Arguments: %d\n", argc);    /* First print */
    
    for (i = 0; i < argc; i++) {
        printf("Argument %d: %s\n", i, argv[i]);
    }
    
    return 0;
}
