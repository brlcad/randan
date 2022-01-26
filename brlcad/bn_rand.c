#include <bn.h>

static unsigned idx = 0;

void seed_bn_rand(long seed) {
  BN_RANDSEED(idx, seed);
}

int rand_bn_rand(void) {
  return (1000000 * BN_RANDOM(idx));
}
