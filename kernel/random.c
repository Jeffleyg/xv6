// random.c
#include "types.h"
#include "param.h"
#include "riscv.h"

static unsigned long seed = 1;

// Simple linear congruential generator
int random(void) {
    seed = seed * 1664525 + 1013904223;
    return (int)(seed & 0x7FFFFFFF);
}

// Seed the random number generator
void srandom(unsigned int s) {
    seed = s;
}
