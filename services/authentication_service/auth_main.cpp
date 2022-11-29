#include "random_generator.h"

int main() {
  RandomGenerator random_generator;
  std::cout << random_generator.GenerateToken();
  return 0;
}