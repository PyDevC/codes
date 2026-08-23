#include <iostream>
#include <vector>

template <typename T> void printVector(const std::vector<T> vec) {
  std::cout << "[";

  // If empty just close
  if (vec.empty()) {
    std::cout << "]" << std::endl;
    return;
  }

  for (auto v : vec) {
    std::cout << v << ", ";
  }

  std::cout << "\b\b]" << std::endl;
}
