#include <iostream>
#include <vector>

class Solution {
  int LCM(int a, int b) {
    int gcd = GCD(a, b);
    int lcm = gcd == 0 ? 0 : (a / gcd) * b;

    return lcm;
  }

  int GCD(int a, int b) {
    int gcd{1};
    int min = std::min(a, b);
    int i{1};
    while (a > 1 && b > 1 && i <= min) {
      if (a % i == 0 && b % i == 0) {
        gcd *= i;
        a /= i;
        b /= i;
      }
      i++;
    }
    return gcd;
  }

public:
  std::vector<int> lcmAndGcd(int a, int b) { return {LCM(a, b), GCD(a, b)}; }
};

int main() {
  Solution sol;
  auto answer = sol.lcmAndGcd(99, 121);
  std::cout << "[" << answer[0] << ", " << answer[1] << "]" << std::endl;
  return 0;
}
