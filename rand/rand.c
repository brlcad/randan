#include <stdlib.h>


void seed_rand(long seed) {
  srand((unsigned)seed);
}

int rand_rand(void) {
  return rand() % 1000000;
}
