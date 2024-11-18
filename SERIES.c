#include <stdio.h>
#include <omp.h>

int main() {
    int n = 10;  // Number of multiples to print

    // Set the number of threads to 2
    omp_set_num_threads(2);

    // Parallel region where two threads print multiples of 2 and 4
    #pragma omp parallel
    {
        int thread_id = omp_get_thread_num();

        // Thread 0 prints multiples of 2
        if (thread_id == 0) {
            for (int i = 1; i <= n; i++) {
                printf("Thread %d: %d\n", thread_id, 2 * i);
            }
        }
        // Thread 1 prints multiples of 4
        else if (thread_id == 1) {
            for (int i = 1; i <= n; i++) {
                printf("Thread %d: %d\n", thread_id, 4 * i);
            }
        }
    }

    return 0;
}

