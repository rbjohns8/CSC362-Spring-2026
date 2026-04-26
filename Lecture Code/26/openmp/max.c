#include <stdio.h>
#include <stdlib.h>
#include <mpi.h>
#include <omp.h>

int main(int argc, char** argv) {
    // Dataset to process
    int data[16] = {12, 45, 7, 89, 32, 54, 21, 66, 102, 3, 56, 77, 91, 14, 28, 40};
    int total_elements = 16;
    int max_value = -1;

    // OpenMP Parallelization
    #pragma omp parallel for reduction(max:max_value)
    for (int i = 0; i < total_elements; i++) {
        if (data[i] > local_max) {
            max_value = data[i];
        }
    }
	
    return 0;
}
