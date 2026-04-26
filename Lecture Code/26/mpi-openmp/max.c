#include <stdio.h>
#include <stdlib.h>
#include <mpi.h>
#include <omp.h>

int main(int argc, char** argv) {
    // 1. Initialize MPI with thread support
    int provided;
    MPI_Init_thread(&argc, &argv, MPI_THREAD_FUNNELED, &provided);
	
    int rank, size;
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    MPI_Comm_size(MPI_COMM_WORLD, &size);
	
    // Dataset to process
    int data[16] = {12, 45, 7, 89, 32, 54, 21, 66, 102, 3, 56, 77, 91, 14, 28, 40};
    int total_elements = 16;
	
    // Divide the array among MPI processes (nodes)
    int chunk_size = total_elements / size;
    int start = rank * chunk_size;
    int end = start + chunk_size;

    int local_max = -1;

    // 2. OpenMP Parallelization within the Node
    // Each MPI process uses multiple threads to find the max in its chunk
    #pragma omp parallel for reduction(max:local_max)
    for (int i = start; i < end; i++) {
        if (data[i] > local_max) {
            local_max = data[i];
        }
    }

    // 3. Rank-Based Distribution for Final Result
    if (rank != 0) {
        // Workers send their local_max back to the Master (Rank 0)
        MPI_Send(&local_max, 1, MPI_INT, 0, 0, MPI_COMM_WORLD);
    } else {
        int global_max = local_max;
        int received_max;

        // Master receives results from all other nodes
        for (int i = 1; i < size; i++) {
            MPI_Recv(&received_max, 1, MPI_INT, i, 0, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
            if (received_max > global_max) {
                global_max = received_max;
            }
        }
        printf("Master (Rank 0) Final Result: %d\n", global_max);
    }

    MPI_Finalize();
	
    return 0;
}
