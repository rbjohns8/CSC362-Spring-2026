#include <stdio.h>
#include <mpi.h>

int main(int argc, char** argv) {
    int rank, size;

    // Initialize MPI environment
    MPI_Init(NULL, NULL);

    // Get rank and size of MPI communicator
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    MPI_Comm_size(MPI_COMM_WORLD, &size);

    // Print message from each process
    printf("Hello from process %d of %d\n", rank, size);

    // Finalize MPI environment
    MPI_Finalize();

    return 0;
}
