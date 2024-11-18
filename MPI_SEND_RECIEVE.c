#include <mpi.h>
#include <stdio.h>

int main(int argc, char* argv[]) {
    int rank, size;

    // Initialize MPI environment
    MPI_Init(&argc, &argv);

    // Get rank of the process
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);

    // Get number of processes
    MPI_Comm_size(MPI_COMM_WORLD, &size);

    int numbers[2]; // Each process will send 2 numbers

    // Assign numbers based on rank
    numbers[0] = rank * 2 + 1; // First number
    numbers[1] = rank * 2 + 2; // Second number

    if (rank != 0) {
        // Non-root processes send their numbers to the root process
        MPI_Send(numbers, 2, MPI_INT, 0, 0, MPI_COMM_WORLD);
    } else {
        // Root process receives numbers from all other processes
        printf("Root process receiving data:\n");
        for (int i = 1; i < size; i++) {
            int received[2];
            MPI_Recv(received, 2, MPI_INT, i, 0, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
            printf("Received from process %d: [%d, %d]\n", i, received[0], received[1]);
        }
    }

    // Finalize MPI environment
    MPI_Finalize();

    return 0;
}

