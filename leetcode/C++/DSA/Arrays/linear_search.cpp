#include "print_functions.h"

auto linearSearch(std::vector<int> &vec, int target) {
  for (auto it{vec.begin()}; it != vec.end(); ++it) {
    if (*it == target) {
      return it;
    }
  }
  return vec.end();
}

int main() {
  std::vector<int> vec = {1, 2, 234, 23, 4, 10};
  int target = 10;

  std::cout << vec << std::endl;
  std::cout << "target = " << target << "\n";

  auto it = linearSearch(vec, target);
  if (it != vec.end()) {
    std::cout << "Element found";
  } else {
    std::cout << "Element not found";
  }
  return 0;
}
