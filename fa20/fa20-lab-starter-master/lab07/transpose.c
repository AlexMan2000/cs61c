#include "transpose.h"

/* The naive transpose function as a reference. */
void transpose_naive(int n, int blocksize, int *dst, int *src) {
    for (int x = 0; x < n; x++) {
        for (int y = 0; y < n; y++) {
            dst[y + x * n] = src[x + y * n];
        }
    }
}

/* The helper function for checking boundaries */
int checkWithinBound(int n, int x, int y) {
    if (x >= n || y >= n || x < 0 || y < 0) {
        return 0;
    }
    return 1;
}


/* Implement cache blocking below. You should NOT assume that n is a
 * multiple of the block size. */
void transpose_blocking(int n, int blocksize, int *dst, int *src) {
    // YOUR CODE HERE
    int exact_group_num = n / blocksize;
    int* dst_;
    int* src_;
    for (int i = 0; i < exact_group_num + 1; i++) {
        for (int j = 0; j < exact_group_num + 1; j++) {
            // Offset Within A Block
            for (int x = 0; x < blocksize; x++) {
                for (int y = 0; y < blocksize; y++) {
                    dst_ = dst + (i * blocksize + x) * n + j * blocksize + y; 
                    src_ = src + (j * blocksize + y) * n + i * blocksize + x;
                    if (checkWithinBound(n, (i * blocksize + x), j * blocksize + y) == 1
                    && checkWithinBound(n, (j * blocksize + y), i * blocksize + x) == 1) {
                        *src_ = *dst_;
                    }
                }
            }         
        }
    }
}



