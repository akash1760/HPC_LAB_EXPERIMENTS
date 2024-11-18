#include <mpi.h>
#include <stdio.h>
#include <string.h>

int main(int argc, char** argv) {
    int rank, size;

    // Initialize MPI environment
    MPI_Init(&argc, &argv);

    // Get the rank of the process
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);

    // Get the number of processes
    MPI_Comm_size(MPI_COMM_WORLD, &size);

    // Print "Hello World" from each process
    printf("Process %d out of %d says: Hello World!\n", rank, size);

    // Buffer for sending and receiving messages
    char message[100];

    if (rank == 0) {
        // Root process
        printf("Root process: Receiving messages...\n");

        for (int i = 1; i < size; i++) {
            // Receive messages from all other processes
            MPI_Recv(message, 100, MPI_CHAR, i, 0, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
            printf("Root process received: %s\n", message);
        }
    } else {
        // Non-root processes send a message to the root process
        sprintf(message, "Hello from process %d", rank);
        MPI_Send(message, strlen(message) + 1, MPI_CHAR, 0, 0, MPI_COMM_WORLD);
    }

    // Finalize the MPI environment
    MPI_Finalize();

    return 0;
}

