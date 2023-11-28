#include <time.h>
#include <stdio.h>
#include <x86intrin.h>
#include "ex1.h"

long long int sum(int vals[NUM_ELEMS]) {
    clock_t start = clock();

    long long int sum = 0;
    for(unsigned int w = 0; w < OUTER_ITERATIONS; w++) {
        for(unsigned int i = 0; i < NUM_ELEMS; i++) {
            if(vals[i] >= 128) {
                sum += vals[i];
            }
        }
    }
    clock_t end = clock();
    printf("Time taken: %Lf s\n", (long double)(end - start) / CLOCKS_PER_SEC);
    return sum;
}

long long int sum_unrolled(int vals[NUM_ELEMS]) {
    clock_t start = clock();
    long long int sum = 0;

    for(unsigned int w = 0; w < OUTER_ITERATIONS; w++) {
        for(unsigned int i = 0; i < NUM_ELEMS / 4 * 4; i += 4) {
            if(vals[i] >= 128) sum += vals[i];
            if(vals[i + 1] >= 128) sum += vals[i + 1];
            if(vals[i + 2] >= 128) sum += vals[i + 2];
            if(vals[i + 3] >= 128) sum += vals[i + 3];
        }

        // TAIL CASE, for when NUM_ELEMS isn't a multiple of 4
        // NUM_ELEMS / 4 * 4 is the largest multiple of 4 less than NUM_ELEMS
        // Order is important, since (NUM_ELEMS / 4) effectively rounds down first
        for(unsigned int i = NUM_ELEMS / 4 * 4; i < NUM_ELEMS; i++) {
            if (vals[i] >= 128) {
                sum += vals[i];
            }
        }
    }
    clock_t end = clock();
    printf("Time taken: %Lf s\n", (long double)(end - start) / CLOCKS_PER_SEC);
    return sum;
}

long long int sum_simd(int vals[NUM_ELEMS]) {
    clock_t start = clock();
    __m128i _127 = _mm_set1_epi32(127); // This is a vector with 127s in it... Why might you need this?
    long long int result = 0; // This is where you should put your final result!
    /* DO NOT MODIFY ANYTHING ABOVE THIS LINE (in this function) */

    for(unsigned int w = 0; w < OUTER_ITERATIONS; w++) {
        /* YOUR CODE GOES HERE */
        // Initialize
        __m128i sum_vec = _mm_setzero_si128();

        for (unsigned int i = 0; i < NUM_ELEMS / 4 * 4; i += 4) {
            // Load four from array
            __m128i tmp = _mm_loadu_si128((__m128i *) (vals + i));
            // Mask the element smaller than 128
            __m128i mask = _mm_cmpgt_epi32(tmp, _127);
            tmp = _mm_and_si128(tmp, mask);
            // Add the the sum vec
            sum_vec = _mm_add_epi32(sum_vec, tmp);
        }
        int tmp_val[4];
        _mm_storeu_si128((__m128i *) tmp_val, sum_vec);

        for (int i = 0; i < 4; i++) {
            result += tmp_val[i]; // This won't cause overflow because we are doing 
            // addition between long long int and int and store the result as a long long int,
            // where long long int result has enough bits to store the tmp_val.
        }
        // result = tmp_val[0] + tmp_val[1] + tmp_val[2] + tmp_val[3]; is not ok, because
        // tmp_val[i] is huge, and any addition operations like tmp_val[i] + tmp_val[j]
        // will cause an overflow(big int + big int), causing the actual result to be smaller than expected.

        /* Hint: you'll need a tail case. */
        for (unsigned int i = NUM_ELEMS / 4 * 4; i < NUM_ELEMS; i++){
            if (vals[i] >= 128) {
                result += vals[i];
            }
        }
    }

    /* DO NOT MODIFY ANYTHING BELOW THIS LINE (in this function) */
    clock_t end = clock();
    printf("Time taken: %Lf s\n", (long double)(end - start) / CLOCKS_PER_SEC);
    return result;
}

long long int sum_simd_unrolled(int vals[NUM_ELEMS]) {
    clock_t start = clock();
    __m128i _127 = _mm_set1_epi32(127);
    long long int result = 0;
    /* DO NOT MODIFY ANYTHING ABOVE THIS LINE (in this function) */

    for(unsigned int w = 0; w < OUTER_ITERATIONS; w++) {
        /* YOUR CODE GOES HERE */
        /* Copy your sum_simd() implementation here, and unroll it */

        __m128i sum_vec = _mm_setzero_si128();

        for (unsigned int i = 0; i < NUM_ELEMS / 16; i++) {
            // Load four from array
            // Unroll 1
            __m128i tmp = _mm_loadu_si128((__m128i *) (vals + i * 16));
            // Mask the element smaller than 128
            __m128i mask = _mm_cmpgt_epi32(tmp, _127);
            tmp = _mm_and_si128(tmp, mask);
            // Add the the sum vec
            sum_vec = _mm_add_epi32(sum_vec, tmp);
            // Unroll 2
            tmp = _mm_loadu_si128((__m128i *) (vals + i * 16 + 4));
            // Mask the element smaller than 128
            mask = _mm_cmpgt_epi32(tmp, _127);
            tmp = _mm_and_si128(tmp, mask);
            // Add the the sum vec
            sum_vec = _mm_add_epi32(sum_vec, tmp);
            // Unroll 3
            tmp = _mm_loadu_si128((__m128i *) (vals + i * 16 + 8));
            // Mask the element smaller than 128
            mask = _mm_cmpgt_epi32(tmp, _127);
            tmp = _mm_and_si128(tmp, mask);
            // Add the the sum vec
            sum_vec = _mm_add_epi32(sum_vec, tmp);
            // Unroll 4
            tmp = _mm_loadu_si128((__m128i *) (vals + i * 16 + 12));
            // Mask the element smaller than 128
            mask = _mm_cmpgt_epi32(tmp, _127);
            tmp = _mm_and_si128(tmp, mask);
            // Add the the sum vec
            sum_vec = _mm_add_epi32(sum_vec, tmp);
        }
        int tmp_val[4];
        _mm_storeu_si128((__m128i *) tmp_val, sum_vec);

        for (int j = 0; j < 4; j++){
            result += tmp_val[j];
        }
        
        /* Hint: you'll need 1 or maybe 2 tail cases here. */
        for (unsigned int i = NUM_ELEMS / 16 * 16; i < NUM_ELEMS; i++){
            if (vals[i] >= 128) {
                result += vals[i];
            }
        }
    }

    /* DO NOT MODIFY ANYTHING BELOW THIS LINE (in this function) */
    clock_t end = clock();
    printf("Time taken: %Lf s\n", (long double)(end - start) / CLOCKS_PER_SEC);
    return result;
}
