#include <fstream>
#include <iostream>
#include <optional>

std::optional<std::string> ReadFile(const std::string &filepath) {
  std::ifstream stream(filepath);
  if (stream) {
    std::string result;
    stream.close();
    return result;
  }
  return {};
}

int main(void) {
  std::optional<std::string> data = ReadFile("data.txt");
  std::string value = data.value_or("Not present");
  std::optional<int> count;
  int c = count.value_or(100);
  if (data.has_value()) {
    std::cout << "File read !!!\n";
  } else {
    std::cout << "Failure to read!!!\n";
  }
  return 0;
}
