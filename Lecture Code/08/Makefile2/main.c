// main.c
#include <stdio.h>
#include "file_utils.h"

int main() {
    const char *filename = "example.txt";
    printf("Reading file: %s\n", filename);
    
    // Read the file and print its contents
    read_and_print_file(filename);

    return 0;
}
