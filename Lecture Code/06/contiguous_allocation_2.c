#include <stdio.h>
#include <stdlib.h>

int main() {
	int n = 5;
	int *arr = (int *)calloc(n, sizeof(int)); // Allocate and initialize to 0

	if (!arr) {
		printf("Memory allocation failed\n");
		return 1;
	}

	// Print array values (should be all 0)
	for (int i = 0; i < n; i++) {
		printf("%d ", arr[i]);
	}
	printf("\n");

	free(arr); // Free memory
	return 0;
}
