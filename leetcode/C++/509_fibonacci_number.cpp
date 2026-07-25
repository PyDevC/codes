#include <iostream>
class Solution {
public:
  int fib(int n) {
    if (n == 0) {
      return 0;
    } else if (n == 1) {
      return 1;
    }
    return fib(n - 1) + fib(n - 2);
  }
};

int main() {
  int number = 3;
  Solution sol;
  std::cout << sol.fib(number);
  return 0;
}
