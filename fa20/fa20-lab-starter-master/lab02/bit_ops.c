#include <stdio.h>
#include "bit_ops.h"

// Return the nth bit of x.
// Assume 0 <= n <= 31
unsigned get_bit(unsigned x,
                 unsigned n) {
    // YOUR CODE HERE
    // Returning -1 is a placeholder (it makes
    // no sense, because get_bit only returns 
    // 0 or 1)
    return (x >> n) & 1;
}
// Set the nth bit of the value of x to v.
// Assume 0 <= n <= 31, and v is 0 or 1
void set_bit(unsigned * x,
             unsigned n,
             unsigned v) {
    // YOUR CODE HERE
    unsigned n_bit = get_bit(*x, n);

    unsigned mask = 1;

    mask = (mask << n);

    unsigned flipped_mask = ~mask;

    // & 111...101....111 when we want to set v from 1 to 0
    if (n_bit == 1 && v == 0) {
        (*x) = (*x) & flipped_mask;
    }


    // | 000...010....000 when we want to set v from 0 to 1
    if (n_bit == 0 && v == 1) {
        (*x) = (*x) | mask;
    }

    // Otherwise, unchanged.
    return;
}
// Flip the nth bit of the value of x.
// Assume 0 <= n <= 31
void flip_bit(unsigned * x,
              unsigned n) {
    // YOUR CODE HERE
    unsigned n_bit = get_bit(*x, n);
    if (n_bit == 0) {
        set_bit(x, n, 1);
    } else {
        set_bit(x, n, 0);
    }
}

