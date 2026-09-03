#include <iostream>

class Solution {
  public:
    int gcd(int a, int b) {
        if (a == 0) { return b; }
        return gcd(b % a, a);
    }
};

int main() {
    Solution sol;
    std::cout << "GCD: " << sol.gcd(60, 36) << std::endl;
    return 0;
}
