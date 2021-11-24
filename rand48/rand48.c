#include <stdlib.h>


void seed_rand48(long seed) {
  srand48((long)seed);
}

int rand_rand48(void) {
  return lrand48() % 1000000;
}
