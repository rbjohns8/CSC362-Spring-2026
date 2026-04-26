#include <stdio.h>
#include <stdlib.h>
#include <omp.h>

int main(int argc, char *argv[])
{
	int n = 100000;
	int i, sum, *a;
	
	if (argc > 1) sscanf(argv[1], "%d", &n);
	
	a = malloc(n * sizeof(int));
	
	if (a == NULL) {
		fprintf(stderr, "Failed to allocate.\n");
		exit(1);
	}
	
	sum = 0;
	
	#pragma omp parallel for reduction(+:sum)
	for (i = 0; i < n; i++) {
		sum += a[i];
	}
	
	printf("SUM: %d\n", sum);
	free(a);
	
	return 0;
}
