#include <array>
#include <iostream>
#include <stdint.h>
#include <vector>

template <typename T, std::size_t SIZE>
std::array<T, SIZE> create_array(T type, std::size_t size) {
  // Since it's created using new keyword it is created on heap so it should not
  // be deleted out of scope
  std::array new_array = new std::array(type, size);
  return new_array;
}

template <typename T> std::vector<T> create_vector(T type) {
  // Since it's created using new keyword it is created on heap so it should not
  // be deleted out of scope
  std::vector new_vector = new std::vector(type);
  return new_vector;
}

template <typename T, std::size_t SIZE>
std::ostream &operator<<(std::ostream &stream, std::array<T, SIZE> arr) {
  stream << "array[";

  for (auto &e : arr) {
    stream << e << ", ";
  }
  stream << "]";
  return stream;
}

int main(void) {
  auto arr = new std::array<int, 10>;
  std::cout << arr << std::endl;
  return 0;
}
