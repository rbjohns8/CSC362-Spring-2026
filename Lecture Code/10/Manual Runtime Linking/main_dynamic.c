#include <stdio.h>
#include <dlfcn.h> // For dynamic linking functions

int main() {
    // Load the shared library at runtime
    void *handle = dlopen("./libmath.so", RTLD_LAZY);
    if (!handle) {
        fprintf(stderr, "Error: %s\n", dlerror());
        return 1;
    }

    // Get pointers to the functions
    void (*add)(int, int) = dlsym(handle, "add");
    if (!add) {
        fprintf(stderr, "Error loading function 'add': %s\n", dlerror());
        dlclose(handle);
        return 1;
    }

    void (*subtract)(int, int) = dlsym(handle, "subtract");
    if (!subtract) {
        fprintf(stderr, "Error loading function 'subtract': %s\n", dlerror());
        dlclose(handle);
        return 1;
    }

    // Use the functions from the dynamically loaded library
    add(5, 3);
    subtract(5, 3);

    // Close the library when done
    dlclose(handle);
    return 0;
}
