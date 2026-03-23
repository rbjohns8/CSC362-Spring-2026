#include <stdio.h>
#include <stdlib.h>

#define MAX_ORDER 10  // Maximum order (2^MAX_ORDER bytes)

// Block structure for buddy allocation
struct Block {
    int is_free;
    size_t size;
    struct Block *buddy;
};

// Buddy allocate function
void *buddy_allocate(size_t size, struct Block *memory, int order) {
    if (order > MAX_ORDER || memory->size < size) return NULL;

    if (memory->is_free && memory->size >= size) {
        while (memory->size > size) {
            size_t new_size = memory->size / 2;
            memory->buddy = memory + new_size;
            memory->size = new_size;
        }
        memory->is_free = 0;
        return (void *)memory;
    }

    return NULL;
}

// Main function to test buddy allocation
int main() {
    struct Block memory = {1, 1024, NULL};  // Initialize memory block as free
    size_t alloc_size = 64;

    void *block = buddy_allocate(alloc_size, &memory, 0);

    if (block) {
        printf("Memory allocated at address: %p\n", block);
    } else {
        printf("Memory allocation failed.\n");
    }

    return 0;
}
