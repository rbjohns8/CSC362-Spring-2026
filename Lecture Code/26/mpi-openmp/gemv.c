#include <stdio.h>
#include <stdlib.h>
#include <mpi.h>
#include <omp.h>

#define N 8 // Total size of the matrix (NxN) and vector (N)

int main(int argc, char** argv) {
    int provided;
    MPI_Init_thread(&argc, &argv, MPI_THREAD_FUNNELED, &provided);

    int rank, size;
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    MPI_Comm_size(MPI_COMM_WORLD, &size);

    int rows_per_node = N / size;
    double matrix[N][N], vector[N], local_res[rows_per_node], global_res[N];
    double local_matrix_slice[rows_per_node][N];

    // 1. Initialization (Master only)
    if (rank == 0) {
        for (int i = 0; i < N; i++) {
            vector[i] = i + 1;
            for (int j = 0; j < N; j++) {
                matrix[i][j] = i + j;
            }
        }
    }

    // 2. Distribute data (MPI)
    // Send the entire vector to everyone, but scatter the matrix rows
    MPI_Bcast(vector, N, MPI_DOUBLE, 0, MPI_COMM_WORLD);
    MPI_Scatter(matrix, rows_per_node * N, MPI_DOUBLE, 
                local_matrix_slice, rows_per_node * N, MPI_DOUBLE, 
                0, MPI_COMM_WORLD);

    // 3. Local Computation (OpenMP)
    // One MPI process per node uses threads to solve its assigned rows
    #pragma omp parallel for
    for (int i = 0; i < rows_per_node; i++) {
        local_res[i] = 0;
        for (int j = 0; j < N; j++) {
            local_res[i] += local_matrix_slice[i][j] * vector[j];
        }
    }

    // 4. Collect results (MPI)
    MPI_Gather(local_res, rows_per_node, MPI_DOUBLE, 
               global_res, rows_per_node, MPI_DOUBLE, 
               0, MPI_COMM_WORLD);

    if (rank == 0) {
        printf("Master (Rank 0) Result Vector:\n");
        for (int i = 0; i < N; i++) printf("%.1f ", global_res[i]);
        printf("\n");
    }

    MPI_Finalize();
	
    return 0;
}
