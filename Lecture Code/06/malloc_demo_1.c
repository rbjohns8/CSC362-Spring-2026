#include <stdio.h>   
#include <stdlib.h> 
 
int main(void) 
{
    // Allocate memory safely
    int *p1 = (int *)malloc(4 * sizeof(int));   // Allocate enough for an array of 4 int
    int *p2 = (int *)malloc(sizeof(int[4]));    // Allocate memory for an array of 4 int
    int *p3 = (int *)malloc(4 * sizeof(*p3));   // Allocate memory without repeating type name

    // Check if malloc() failed
    if (!p1 || !p2 || !p3) {
        fprintf(stderr, "Memory allocation failed!\n");

        // Free allocated memory before exiting
        free(p1);
        free(p2);
        free(p3);
        return 1; // Exit with error
    }

    // Use p1 safely since it's allocated
    for (int n = 0; n < 4; ++n) // Populate the array
        p1[n] = n * n;
    
    for (int n = 0; n < 4; ++n) // Print values
        printf("p1[%d] == %d\n", n, p1[n]);

    // Free allocated memory
    free(p1);
    free(p2);
    free(p3);

    return 0; 
}
