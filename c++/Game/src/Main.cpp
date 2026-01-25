#include <algorithm>
#include <iostream>
#include <vector>

int main(void) {
  // sorting
  std::vector<int> v = {1, 23, 234234, 234, 234, 234, 23};
  std::sort(v.begin(), v.end(), [](int a, int b) {
    if (a >= 100) {
      return a > b;
    } else {
      return a < b;
    }
  });
  for (int value : v) {
    std::cout << value << std::endl;
  }
  return 0;
}
