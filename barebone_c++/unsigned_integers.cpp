#include <iostream>

int main() {
  // There is no difference whether unsigned keyword is before or after the type
  int unsigned x = 10;
  unsigned int y = 10;
  std::cout << x << y << std::endl; // output: 1010

  unsigned short a{};
  unsigned int b{};
  unsigned long c{};
  unsigned long long d{};

  std::cout << "Compute Sizeof: \n";
  std::cout << "unsigned short: " << sizeof(a) << "\n";
  std::cout << "unsigned int: " << sizeof(b) << "\n";
  std::cout << "unsigned long: " << sizeof(c) << "\n";
  std::cout << "unsigned long long: " << sizeof(d) << "\n";

  // unsigned integers can never overflow
  a = 100000; // this will give you compiler warning but that's ok
  b = 100000 % 65536;
  if (a == b) {
    std::cout << "Implicit conversion: 100000 to 34464\n";
  } else {
    std::cout << "Not conversions, value get's overflowed";
  }

  return 0;
}
