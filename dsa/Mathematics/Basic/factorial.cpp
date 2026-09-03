#include <iostream>

class Solution {
public:
  // No recursion
  int factorial(int n) {
    if (n < 2) {
      return n;
    }

    int fact{1};
    for (int i{2}; i <= n; ++i) {
      fact *= i;
    }

    return fact;
  }
};

int main() {
  Solution sol;
  std::cout << sol.factorial(5) << std::endl;
  return 0;
}
