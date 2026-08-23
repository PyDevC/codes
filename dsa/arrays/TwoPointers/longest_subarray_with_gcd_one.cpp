#include "helper.hpp"

class Solution {
  int getGCD(int a, int b) {
    if (a == 0 || b == 0) {
      return std::max(a, b);
    }

    int i{1};
    int gcd{1};
    int min = std::min(a, b);
    while (a > 1 && b > 1 && i <= min) {
      if (a % i == 0 && b % i == 0) {
        a = a / i;
        b = b / i;
        gcd *= i;
      }
      i++;
    }

    return gcd;
  }

public:
  int longestSubarray(std::vector<int> &arr) {
    if (arr.empty()) {
      return 0;
    } else if (arr.size() == 1) {
      return -1;
    }

    int n = static_cast<int>(arr.size());

    int gcd = getGCD(arr[0], arr[1]);
    for (int i{2}; i < n; ++i) {
      gcd = getGCD(arr[i], gcd);
    }

    return gcd != 1 ? -1 : n;
  }
};

int main() {
  std::vector<int> arr = {782, 65};
  Solution sol;
  std::cout << sol.longestSubarray(arr) << std::endl;

  return 0;
}
