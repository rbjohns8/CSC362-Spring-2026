#include <stdio.h>
#include <stdlib.h>

// First fit allocation function
void *first_fit(size_t size, void *memory, size_t mem_size) {
    char *mem = (char *)memory;
    for (size_t i = 0; i < mem_size - size; i++) {
        if (mem[i] == 0) {
            int fits = 1;
            for (size_t j = 0; j < size; j++) {
                if (mem[i + j] != 0) {
                    fits = 0;
                    break;
                }
            }
            if (fits) return (void *)(mem + i);
        }
    }
    return NULL;
}

// Main function to test first fit allocation
int main() {
    size_t mem_size = 1024;
    char memory[mem_size];
    for (size_t i = 0; i < mem_size; i++) memory[i] = 0;  // Initialize all memory to 0

    size_t alloc_size = 50;
    void *block = first_fit(alloc_size, memory, mem_size);

    if (block) {
        printf("Memory allocated at address: %p\n", block);
    } else {
        printf("Memory allocation failed.\n");
    }

    return 0;
}
