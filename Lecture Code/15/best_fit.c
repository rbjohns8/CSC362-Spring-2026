#include <stdio.h>
#include <stdlib.h>

// Best fit allocation function
void *best_fit(size_t size, void *memory, size_t mem_size) {
    char *mem = (char *)memory;
    void *best = NULL;
    size_t best_size = mem_size + 1;

    for (size_t i = 0; i < mem_size - size; i++) {
        if (mem[i] == 0) {
            size_t j = i;
            while (j < mem_size && mem[j] == 0) j++;
            if (j - i >= size && j - i < best_size) {
                best = mem + i;
                best_size = j - i;
            }
            i = j;
        }
    }
    return best;
}

// Main function to test best fit allocation
int main() {
    size_t mem_size = 1024;
    char memory[mem_size];
    for (size_t i = 0; i < mem_size; i++) memory[i] = 0;  // Initialize memory

    size_t alloc_size = 50;
    void *block = best_fit(alloc_size, memory, mem_size);

    if (block) {
        printf("Memory allocated at address: %p\n", block);
    } else {
        printf("Memory allocation failed.\n");
    }

    return 0;
}
