#include <stdio.h>

int main() {
    
    //String Literal Initialization
    //char str[] = "Hello";
    //printf("String: %s\n", str);

    //Manual Character Array Initialization
    //char str[5] = {'H', 'e', 'l', 'l', 'o'};
    // Undefined behavior
    //printf("String: %s\n", str);  

    //char str[6] = {'H', 'e', 'l', 'l', 'o', '\0'};
    // Safe and predictable behavior
    //printf("String: %s\n", str);

    //Partial Initialization
    char str[10] = "Hi";
    //The array str will contain {'H', 'i', '\0', 0, 0, 0, 0, 0, 0, 0}.
    
    // Print all elements in the array, including zero-initialized ones
    for (int i = 0; i < 10; i++) {
        //Check if the character is a null terminator (which should only be at str[2])
        if (str[i] == '\0' && i == 2) {
            printf("Element %d: \\0 (null terminator)\n", i);
        } else if (str[i] == 0) {
            printf("Element %d: 0\n", i);
        } else {
            printf("Element %d: %c\n", i, str[i]);
        }
    }
    
    
    return 0;
}




