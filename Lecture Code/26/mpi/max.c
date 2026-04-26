#include <stdio.h>
#include <stdlib.h>
#include <mpi.h>

int main(int argc, char** argv) {
    MPI_Init(&argc, &argv);

    int rank, size;
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    MPI_Comm_size(MPI_COMM_WORLD, &size);

    // Let's imagine we have a shared list of numbers
    int data[8] = {12, 45, 7, 89, 32, 54, 21, 66};
    
    // Each process calculates which part of the array to check
    // If size is 4, each process checks 2 numbers.
    int chunk_size = 8 / size;
    int start = rank * chunk_size;
    int end = start + chunk_size;
	
    int local_max = -1;
	
    // WORKER TASK: Find the max in their assigned "slice"
    for (int i = start; i < end; i++) {
        if (data[i] > local_max) {
            local_max = data[i];
        }
    }
	
    printf("Rank %d found local max: %d\n", rank, local_max);
	
    // RANK-BASED DISTRIBUTION
    if (rank != 0) {
        // Workers send their local max back to the Master (Rank 0)
        MPI_Send(&local_max, 1, MPI_INT, 0, 0, MPI_COMM_WORLD);
    } else {
        // MASTER TASK: Collect all results and find the final answer
        int global_max = local_max;
        int received_max;
		
        for (int i = 1; i < size; i++) {
            MPI_Recv(&received_max, 1, MPI_INT, i, 0, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
            if (received_max > global_max) {
                global_max = received_max;
            }
        }
		
        printf("Master (Rank 0) declares the global maximum is: %d\n", global_max);
    }
	
    MPI_Finalize();
	
    return 0;
}
