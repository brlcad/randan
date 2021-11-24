#include <ctime>
#include <iostream>
#include <iomanip>
#include <vector>


#define DECLARE_C(x) extern "C" { \
  void seed_##x(long seed); \
  int rand_##x(void); \
}

#define DECLARE_CPP(x) \
  void seed_##x(long seed); \
  int rand_##x(void);


DECLARE_C(rand);
DECLARE_C(random);
DECLARE_C(rand48);
DECLARE_CPP(mt19937);


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

  std::string names[] = {"rand", "random", "rand48", "mt19937"};
  void (*seed[])(long) = {seed_rand, seed_random, seed_rand48, seed_mt19937, nullptr};
  int (*rfunc[])(void) = {rand_rand, rand_random, rand_rand48, rand_mt19937, nullptr};

  for(int i = 0; seed[i] != nullptr; i++) {
    seed[i](time(0));
  }

  /* print headers */
  for(int i = 0; rfunc[i] != nullptr; i++) {
    std::cerr << std::setw(10) << names[i] << std::tab;
  }
  std::cerr << std::endl;
  for(size_t i = 0; rfunc[i] != nullptr; i++) {
    size_t maxj = (names[i].length()) < 10 ? 10 : names[i].length();
    for(size_t j = 0; j < maxj; j++) {
      std::cerr << "-";
    }
    if (rfunc[i+1] != nullptr)
      std::cerr << std::tab;
  }
  std::cerr << std::endl;

  while (count--) {
    for(int i = 0; rfunc[i] != nullptr; i++) {
      std::cout << std::setw(10) << rfunc[i]() << std::tab;
    }
    std::cout << std::endl;
  }

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
