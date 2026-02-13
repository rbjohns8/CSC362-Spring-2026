// file_utils.c
#include <stdio.h>
#include "file_utils.h"

// Reads a file and prints its contents to the console
void read_and_print_file(const char *filename) {
    FILE *file = fopen(filename, "r");
    if (file == NULL) {
        perror("Error opening file");
        return;
    }

    char ch;
    while ((ch = fgetc(file)) != EOF) {
        putchar(ch);
    }

    fclose(file);
}
