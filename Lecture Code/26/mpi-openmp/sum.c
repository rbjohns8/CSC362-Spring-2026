#include <stdio.h>
#include <stdlib.h>
#include <omp.h>
#include <mpi.h>

int main(int argc, char *argv[])
{
	int n = 100000;
	int p, i, *a;
	int local_sum, global_sum;
	int size, rank;
	
	MPI_Init(&argc, &argv);
	MPI_Comm_size(MPI_COMM_WORLD, &size);
	MPI_Comm_rank(MPI_COMM_WORLD, &rank);
	
	if (argc > 1) sscanf(argv[1], "%d", &n);
	
	// block of array elements for each node
	p = n / size;
	a = malloc(p * sizeof(int));
	
	if (a == NULL) {
		fprintf(stderr, "Node %d failed to allocate A.\n", rank);
		MPI_Finalize();
		exit(1);
	}
	
	MPI_Barrier(MPI_COMM_WORLD);
	
	global_sum = 0;
	local_sum = 0;
	
	#pragma omp parallel for reduction(+:local_sum)
	for (i = 0; i < p; i++) {
		local_sum += a[i];
	}
	
	MPI_Reduce(&local_sum, &global_sum, 1, MPI_INT, MPI_SUM, 0, MPI_COMM_WORLD);
	MPI_Barrier(MPI_COMM_WORLD);
	
	free(a);
	MPI_Finalize();
	
	return 0;
}
