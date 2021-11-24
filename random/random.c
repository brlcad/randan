#include <stdlib.h>


void seed_random(long seed) {
  srandom((unsigned)seed);
}

int rand_random(void) {
  return random() % 1000000;
}
