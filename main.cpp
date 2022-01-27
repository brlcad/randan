#include <ctime>
#include <cmath>
#include <iostream>
#include <iomanip>
#include <vector>


#define DECLARE_C(x) extern "C" { \
  void seed_##x(long seed); \
  int rand_##x(void); \
} \
extern int __x

#define DECLARE_CPP(x) \
  void seed_##x(long seed); \
  int rand_##x(void)


DECLARE_C(rand);
DECLARE_C(random);
DECLARE_C(rand48);
DECLARE_CPP(mt19937);
DECLARE_C(bn_rand);
DECLARE_C(bn_randhalf);


namespace std {
  template <typename _char, typename _traits>
  inline basic_ostream<_char, _traits> &
  tab(basic_ostream<_char, _traits> &__ostream) {
    return __ostream.put(__ostream.widen('\t'));
  }
}


int main(int ac, char *av[]) {

  if (ac > 2) {
    std::cout << "Usage: " << av[0] << " [count]" << std::endl;
    return 1;
  }

  int count = 1;
  if (ac == 2) {
    count = abs(atoi(av[1]));
  }
  if (count < 0) {
    std::cout << "Usage: " << av[0] << " [count]" << std::endl;
    return 2;
  }

  std::string names[] = {"rand()", "random()", "lrand48()", "std::mt19937", "BN_RANDOM", "bn_randhalf"};
  void (*seed[])(long) = {seed_rand, seed_random, seed_rand48, seed_mt19937, seed_bn_rand, seed_bn_randhalf, nullptr};
  int (*rfunc[])(void) = {rand_rand, rand_random, rand_rand48, rand_mt19937, rand_bn_rand, rand_bn_randhalf, nullptr};
  size_t generators = 0;
  for(size_t i = 0; seed[i] != nullptr; i++) {
    generators++;
   }
  

  /* print intro */
  std::cerr << "\"randan\" v1.0.0 by C.S. Morrison" << std::endl << std::endl;
  std::cerr << "  Usage: " << av[0] << " [count]" << std::endl;
  std::cerr << "  Generating " << count << " pseudorandom number" << ((count!=1)? "s " : " ") << "using " << generators << " implementations" << std::endl;
  std::cerr << "  with uniform distribution within [0, 1000000)" << std::endl << std::endl;

  /* print headers */
  for(size_t i = 0; i < generators; i++) {
    std::cerr << std::setw(10) << names[i] << std::tab;
  }
  std::cerr << std::endl;
  for(size_t i = 0; i < generators; i++) {
    size_t maxj = (names[i].length()) < 10 ? 10 : names[i].length();
    for(size_t j = 0; j < maxj; j++) {
      std::cerr << "-";
    }
    if (rfunc[i+1] != nullptr)
      std::cerr << std::tab;
  }
  std::cerr << std::endl;

  /* seed all the generators */
  for(size_t i = 0; i < generators; i++) {
    seed[i](time(0));
  }

  /* generate all the randoms */
  double *totals = new double[generators];
  double *nums = new double[generators * count];
  double *mins = new double[generators];
  double *maxs = new double[generators];
  for(size_t i = 0; i < generators; i++) {
    maxs[i] = nums[i] = 0.0;
    mins[i] = 1000000.0;
  }
  
  for(size_t i = 0; i < generators; i++) {
    for (int j = 0; j < count; j++) {
      nums[(i*count)+j] = rfunc[i]();
    }
    for (int j = 0; j < count; j++) {
      totals[i] += nums[(i*count)+j] / 1000000.0;
    }
    for (int j = 0; j < count; j++) {
      if (nums[(i*count)+j] < mins[i])
	mins[i] = nums[(i*count)+j];
      if (nums[(i*count)+j] > maxs[i])
	maxs[i] = nums[(i*count)+j];
    }
  }
  
  /* print a summary */
  std::cout << "%DEV" << std::endl;
  for(size_t i = 0; i < generators; i++) {
    std::cout << std::setw(3) << fabs(totals[i] - ((double)count/2.0)) / (double)count * 100.0 << std::tab;
  }
  std::cout << std::endl;

  std::cout << "MINS" << std::endl;
  for(size_t i = 0; i < generators; i++) {
    std::cout << std::setw(3) << mins[i] << std::tab;
  }
  std::cout << std::endl;

  std::cout << "MAXS" << std::endl;
  for(size_t i = 0; i < generators; i++) {
    std::cout << std::setw(3) << maxs[i] << std::tab;
  }
  std::cout << std::endl;

  delete [] totals;
  delete [] nums;

  return 0;


  /* TODO: evaluate periodicity */
#if 0
  int seq[10];
  for (int i = 0; i < 10; i++) {
    seq[i] = rfunc();
  }

  unsigned long long tries = 0;
  while (1) {
    tries++;

    //    std::cout << rand() << std::endl;

    if (rfunc() == seq[0] &&
        rfunc() == seq[1] &&
        rfunc() == seq[2] &&
        rfunc() == seq[3] &&
        rfunc() == seq[4] &&
        rfunc() == seq[5] &&
        rfunc() == seq[6] &&
        rfunc() == seq[7] &&
        rfunc() == seq[8] &&
        rfunc() == seq[9]) {
      std::cout << "appears periodic after " << tries << " iterations" << std::endl;
      break;
    }
  }

  return 0;
#endif
}
