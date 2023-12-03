#include "ex2.h"

void v_add_naive(double* x, double* y, double* z) {
    #pragma omp parallel
    {
        for(int i=0; i<ARRAY_SIZE; i++)
            z[i] = x[i] + y[i];
    }
}

// Adjacent Method
void v_add_optimized_adjacent(double* x, double* y, double* z) {
    // TODO: Implement this function
    // Do NOT use the `for` directive here!
    #pragma omp parallel 
    {
        int total_num_thread = omp_get_num_threads();
        int thread_id = omp_get_thread_num();
        int stride = thread_id % total_num_thread;
        for (int i = stride; i < ARRAY_SIZE; i += total_num_thread) {
            z[i] = x[i] + y[i];
        }
    }
}

// Chunks Method
void v_add_optimized_chunks(double* x, double* y, double* z) {
    // TODO: Implement this function
    // Do NOT use the `for` directive here!
    #pragma omp parallel 
    {
        int total_num_thread = omp_get_num_threads();
        int thread_id = omp_get_thread_num();
        // Compute the total number of full chunks
        // Chunk Logic
        int equal_chunk_size = ARRAY_SIZE / total_num_thread;
        int tail_chunk_size = ARRAY_SIZE - ARRAY_SIZE / total_num_thread * (total_num_thread - 1);

        // Deal with the equal_size chunk
        if (thread_id < total_num_thread - 1) {
            // printf("thread id %d dealing with equal size\n", thread_id);
            int start_index = thread_id * equal_chunk_size;
            for (int i = 0; i < equal_chunk_size; i++) {
                z[start_index + i] = x[start_index + i] + y[start_index + i];
            }
        } else {
            // Deal with the tail chunk
            // printf("thread id %d dealing with tail chunk\n", thread_id);
            int start_index = (total_num_thread - 1) * equal_chunk_size;
            for (int i = 0; i < tail_chunk_size; i++) {
                z[start_index + i] = x[start_index + i] + y[start_index + i];
            }
        }
    }
}
