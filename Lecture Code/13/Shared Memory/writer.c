// writer.c
#include <stdio.h>
#include <stdlib.h>
#include <sys/mman.h>
#include <fcntl.h>
#include <unistd.h>
#include <string.h>

int main() {
    const int SIZE = 4096;
    const char *name = "shared_memory";
    int shm_fd;
    char *ptr;

    // Create shared memory object
    shm_fd = shm_open(name, O_CREAT | O_RDWR, 0666);
    ftruncate(shm_fd, SIZE);

    // Map shared memory object into memory
    ptr = (char *)mmap(0, SIZE, PROT_WRITE, MAP_SHARED, shm_fd, 0);

    // Write to shared memory
    sprintf(ptr, "Hello from the first process!");

    // Close shared memory
    munmap(ptr, SIZE);
    close(shm_fd);
    
    return 0;
}
