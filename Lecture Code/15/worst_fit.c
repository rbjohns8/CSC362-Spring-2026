#include <stdio.h>
#include <stdlib.h>

// Worst fit allocation function
void *worst_fit(size_t size, void *memory, size_t mem_size) {
    char *mem = (char *)memory;
    void *worst = NULL;
    size_t worst_size = 0;

    for (size_t i = 0; i < mem_size - size; i++) {
        if (mem[i] == 0) {
            size_t j = i;
            while (j < mem_size && mem[j] == 0) j++;
            if (j - i >= size && j - i > worst_size) {
                worst = mem + i;
                worst_size = j - i;
            }
            i = j;
        }
    }
    return worst;
}

// Main function to test worst fit allocation
int main() {
    size_t mem_size = 1024;
    char memory[mem_size];
    for (size_t i = 0; i < mem_size; i++) memory[i] = 0;

    size_t alloc_size = 50;
    void *block = worst_fit(alloc_size, memory, mem_size);

    if (block) {
        printf("Memory allocated at address: %p\n", block);
    } else {
        printf("Memory allocation failed.\n");
    }

    return 0;
}
