#include <mpi.h>
#include <stdio.h>
#include <stdlib.h>

int main(int argc, char** argv) {
    int rank, size, n = 10; // Number of integers to sum (example: n = 10)
    int local_sum = 0, global_sum = 0;
    int chunk_size, start, end;

    // Initialize MPI environment
    MPI_Init(&argc, &argv);
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    MPI_Comm_size(MPI_COMM_WORLD, &size);

    // Root process generates the array of numbers
    int* numbers = NULL;
    if (rank == 0) {
        numbers = (int*)malloc(n * sizeof(int));
        for (int i = 0; i < n; i++) {
            numbers[i] = i + 1; // Example: numbers = [1, 2, 3, ..., n]
        }
    }

    // Broadcast the number of integers and divide work among processes
    MPI_Bcast(&n, 1, MPI_INT, 0, MPI_COMM_WORLD);
    chunk_size = n / size;
    start = rank * chunk_size;
    end = (rank == size - 1) ? n : start + chunk_size;

    // Each process calculates its local sum
    int* local_numbers = (int*)malloc(chunk_size * sizeof(int));
    MPI_Scatter(numbers, chunk_size, MPI_INT, local_numbers, chunk_size, MPI_INT, 0, MPI_COMM_WORLD);
    for (int i = 0; i < chunk_size; i++) {
        local_sum += local_numbers[i];
    }

    // Ring topology: Send and receive partial sums
    int partial_sum = local_sum;
    for (int step = 0; step < size; step++) {
        int neighbor = (rank + 1) % size; // Next process in the ring
        int sender = (rank - 1 + size) % size; // Previous process in the ring

        // Send partial sum to the next neighbor
        MPI_Send(&partial_sum, 1, MPI_INT, neighbor, 0, MPI_COMM_WORLD);

        // Receive partial sum from the previous neighbor
        int received_sum = 0;
        MPI_Recv(&received_sum, 1, MPI_INT, sender, 0, MPI_COMM_WORLD, MPI_STATUS_IGNORE);

        // Add received partial sum to local partial sum
        partial_sum += received_sum;
    }

    // Root process prints the final sum
    if (rank == 0) {
        global_sum = partial_sum; // After the last step, rank 0 holds the final sum
        printf("The total sum of the first %d integers is: %d\n", n, global_sum);
    }

    // Clean up
    free(local_numbers);
    if (rank == 0) {
        free(numbers);
    }

    MPI_Finalize();
    return 0;
}

