// Problem Statement
// A Person can Take m steps on a N case Staircase.
// Calculate the number of ways a person can climb the stairs.

#include <iostream>

int nStairCaseWays(int n, int m) {
  if (n == 0) {
    return 1;
  }

  int ways{};
  for (int i{1}; i <= m; ++i) {
    if (n >= i) {
      ways += nStairCaseWays(n - i, m);
    }
  }
  return ways;
}

int main() {
  for (int i{}; i < 10; ++i) {
    std::cout << "For N = " << i << " Number of Ways: " << nStairCaseWays(i, 3)
              << std::endl;
  }
  return 0;
}
