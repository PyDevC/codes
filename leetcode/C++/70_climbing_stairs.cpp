#include <iostream>
#include <vector>

class Solution {
public:
  int climbStairs(int n) {
    if (n <= 2) {
      return n;
    }
    int prev = 0;
    int prev2 = 1;
    int current = prev + prev2;
    for (int i{2}; i <= n; ++i) {
      prev2 = prev;
      prev = current;
      current = prev + prev2;
    }
    return current;
  }
};

int main() {
  Solution sol;
  std::cout << sol.climbStairs(3) << std::endl;
  std::cout << sol.climbStairs(4) << std::endl;
  std::cout << sol.climbStairs(10) << std::endl;
  std::cout << sol.climbStairs(6) << std::endl;
  std::cout << sol.climbStairs(8) << std::endl;
}
