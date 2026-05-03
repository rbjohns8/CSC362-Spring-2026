#include <stdio.h>
#include <stdlib.h>
#include <mpi.h>

int main(int argc, char** argv) {
	int data[16] = {12, 45, 7, 89, 32, 54, 21, 66, 102, 3, 56, 77, 91, 14, 28, 40};
    int total_elements = 16;
    int local_max = -1;
	int global_max, i;
    int rank, size;
	int chunk_size, start, end;

	MPI_Init(NULL, NULL);
	
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    MPI_Comm_size(MPI_COMM_WORLD, &size);
	
	chunk_size = total_elements / size;
	start = rank * chunk_size;
	end = start + chunk_size;
	
	for (i = start; i < end; i++) {
		if (local_max < data[i])
			local_max = data[i];
	}
	
	MPI_Reduce(&local_max, &global_max, 1, MPI_INT, MPI_MAX, 0, MPI_COMM_WORLD);
	
	MPI_Finalize();

	if (rank == 0)
		printf("Max Value is: %d\n", global_max);

	return 0;
}
