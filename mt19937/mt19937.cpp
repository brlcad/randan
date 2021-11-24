#include <random>

std::random_device dev;
std::mt19937 rng(dev());
std::uniform_int_distribution<int> mt(0, 1000000);

void seed_mt19937(long seed) {
  rng.seed(static_cast<std::mt19937::result_type>(seed));
}

int rand_mt19937(void) {
  return mt(rng);
}
