#include <stdio.h>
#include <omp.h>

int main() {
    // Initialize val outside of parallel region
    int val = 1234;
    
    // Print the initial value of val
    printf("Initial value of val: %d\n", val);
    
    // Set the number of threads to 4
    omp_set_num_threads(4);
    
    // Enter parallel region
    #pragma omp parallel firstprivate(val)
    {
        int thread_id = omp_get_thread_num(); // Get the current thread's ID
        
        // Print the value of val before incrementing inside the parallel region
        printf("Thread %d: Initial value of val: %d\n", thread_id, val);
        
        // Increment val
        val += 1;
        
        // Print the updated value of val after incrementing
        printf("Thread %d: Updated value of val: %d\n", thread_id, val);
    }

    // Print the final value of val outside the parallel region
    printf("Final value of val outside parallel region: %d\n", val);

    return 0;
}

