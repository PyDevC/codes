#include <iostream>

class Solution {
public:
  int reverseDigits(int n) {
    int reversed{};
    int sum{1};
    int remainder{};
    while (n > 0) {
      reversed *= 10;
      reversed += n % 10;
      n /= 10;
    }
    return reversed;
  }
};

int main() {
  Solution sol;
  std::cout << sol.reverseDigits(1221) << std::endl;
  return 0;
}
