#include <iostream>
#include <variant>

int main(void) {
  std::variant<std::string, int> data;
  data = "Cherno";
  std::cout << std::get<std::string>(data) << "\n";
  data = 10;
  std::cout << std::get<int>(data) << "\n";
  return 0;
}
