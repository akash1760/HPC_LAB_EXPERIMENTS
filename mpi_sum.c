#include <mpi.h>
#include <stdio.h>

int main(int argc, char* argv[]) {
    int rank, size;
    long long N = 10000; // Default value of N
    long long local_sum = 0, total_sum = 0;

    // Initialize MPI environment
    MPI_Init(&argc, &argv);

    // Get the rank and size
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    MPI_Comm_size(MPI_COMM_WORLD, &size);

    // Compute range of numbers for this process
    long long start = (rank * N) / size + 1;
    long long end = ((rank + 1) * N) / size;

    // Each process calculates its local sum
    for (long long i = start; i <= end; i++) {
        local_sum += i;
    }

    // Each process prints its local sum
    printf("Process %d: Local sum of range [%lld, %lld] = %lld\n", rank, start, end, local_sum);

    // Reduce all local sums into the total sum at the root process
    MPI_Reduce(&local_sum, &total_sum, 1, MPI_LONG_LONG, MPI_SUM, 0, MPI_COMM_WORLD);

    // Root process prints the result
    if (rank == 0) {
        printf("Total sum of first %lld integers: %lld\n", N, total_sum);
    }

    // Finalize MPI environment
    MPI_Finalize();

    return 0;
}

