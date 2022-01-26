#include <bn.h>

static float idx = 0;
static float *pidx = &idx;

void seed_bn_randhalf(long seed) {
  bn_rand_init(pidx, seed);
}

int rand_bn_randhalf(void) {
  return (1000000 * bn_rand0to1(pidx));
}
