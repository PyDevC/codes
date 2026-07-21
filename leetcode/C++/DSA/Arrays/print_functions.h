#include <iostream>
#include <vector>

template <typename T>
std::ostream &operator<<(std::ostream &stream, std::vector<T> arr) {
  stream << "[ ";
  for (auto a : arr) {
    stream << a << ", ";
  }

  stream << "\b\b ]";
  return stream;
}
