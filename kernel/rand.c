// kernel/rand.c
#include "types.h"
#include "param.h"
#include "spinlock.h"

/*  LCG clássico – “Numerical Recipes”
 *  Xₙ₊₁ = (a·Xₙ + c) mod 2³²
 */
static struct {
  struct spinlock lock;
  uint x;
} rnd;

void
randinit(uint seed)
{
  initlock(&rnd.lock, "rand");
  rnd.x = seed ? seed : 123456789;   // seed ≠0; fallback fixo
}

// Retorna um pseudo-aleatório de 32 bits.
uint
rand(void)
{
  acquire(&rnd.lock);
  rnd.x = rnd.x * 1664525U + 1013904223U;
  uint r = rnd.x;
  release(&rnd.lock);
  return r;
}
