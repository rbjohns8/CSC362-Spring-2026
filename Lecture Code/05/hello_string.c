#include <stdio.h>

int main() {
    char str[5] = {'H', 'e', 'l', 'l', 'o'};
    // Undefined behavior
    printf("String: %s\n", str);

    //char str[6] = {'H', 'e', 'l', 'l', 'o', '\0'};
    // Safe and predictable behavior
    //printf("String: %s\n", str);

    return 0;
}
