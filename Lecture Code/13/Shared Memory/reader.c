// reader.c
#include <stdio.h>
#include <stdlib.h>
#include <sys/mman.h>
#include <fcntl.h>
#include <unistd.h>

int main() {
    const int SIZE = 4096;
    const char *name = "shared_memory";
    int shm_fd;
    char *ptr;

    // Open the shared memory object
    shm_fd = shm_open(name, O_RDONLY, 0666);

    // Map the shared memory object into the process's address space
    ptr = (char *)mmap(0, SIZE, PROT_READ, MAP_SHARED, shm_fd, 0);

    // Read from the shared memory
    printf("Message from shared memory: %s\n", ptr);

    // Close shared memory
    munmap(ptr, SIZE);
    close(shm_fd);
    
    // Optionally remove the shared memory object
    shm_unlink(name);

    return 0;
}
