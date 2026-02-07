#include <stdio.h>

int main() {
#ifdef _WIN32
    printf("This is Windows.\n");
#elif __linux__
    printf("This is Linux.\n");
#elif __APPLE__
    printf("This is macOS.\n");
#else
    printf("Unknown operating system.\n");
#endif
    return 0;
}

