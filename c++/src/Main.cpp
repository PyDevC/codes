#include <iostream>

void Log(const char *message) { std::cout << message << std::endl; }

int main() {
  std::cout << "Hello, World!" << std::endl;
  std::cin.get();
  return 0;
}
