#include <stdio.h>
#include <omp.h>

#define N 100  // Total number of iterations
#define CHUNK 10  // Number of iterations per chunk

int main() {
    // Array to store results (example of work done in the loop)
    int result[N];

    // Initialize the array to zero
    for (int i = 0; i < N; i++) {
        result[i] = 0;
    }

    // Set the number of threads to use
    int num_threads = 4;
    omp_set_num_threads(num_threads);

    // Parallel region with static scheduling and chunk size
    #pragma omp parallel for schedule(static, CHUNK)
    for (int i = 0; i < N; i++) {
        int thread_id = omp_get_thread_num();  // Get the current thread ID
        result[i] = i * 2;  // Simulating work: store i*2 in the result array
        printf("Thread %d processing iteration %d (value %d)\n", thread_id, i, result[i]);
    }

    // Print the final result
    printf("\nFinal results:\n");
    for (int i = 0; i < N; i++) {
        printf("result[%d] = %d\n", i, result[i]);
    }

    return 0;
}

