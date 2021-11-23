#include <ctime>
#include <cstdlib>
#include <iostream>

int main(int ac, char *av[]) {

  if (ac > 2) {
    std::cout << "Usage: " << av[0] << " [count]" << std::endl;
    return 1;
  }

  int count = 1;
  if (ac == 2) {
    count = abs(atoi(av[1]));
  }

  srand(time(0));
  while (count--) {
    std::cout << rand() << std::endl;
  }

  return 0;
}
