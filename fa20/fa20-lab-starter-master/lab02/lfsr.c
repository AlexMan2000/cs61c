#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <string.h>
#include "lfsr.h"

uint16_t get_bit(uint16_t reg, uint16_t n) {
    return (1 & (reg >> n));
}


void set_bit(uint16_t *reg, uint16_t n, uint16_t v) {
    uint16_t mask = ~(1<<n);
    (*reg) = ((*reg) & mask) | (v << n);
}


void lfsr_calculate(uint16_t *reg) {
    /* YOUR CODE HERE */
    uint16_t reg0 = get_bit(*reg, 0);
    uint16_t reg2 = get_bit(*reg, 2);
    uint16_t reg3 = get_bit(*reg, 3);
    uint16_t reg5 = get_bit(*reg, 5);
    (*reg) = (*reg) >> 1;
    uint16_t new_reg_15 = ((reg0^reg2)^reg3)^reg5;
    set_bit(reg, 15, new_reg_15);
}


