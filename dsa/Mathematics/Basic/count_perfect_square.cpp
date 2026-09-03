#include <iostream>
#include <cmath>

class Solution {
  public:
    int countSquares(int n) {
        double root = std::sqrt(n);
        return root > static_cast<int>(root)? root : root - 1;
    }
};

int main() {
    Solution sol;
    std::cout << sol.countSquares(234) << std::endl;
    return 0;
}
