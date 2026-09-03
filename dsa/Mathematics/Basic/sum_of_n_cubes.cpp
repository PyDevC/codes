#include <iostream>

class Solution {
  public:
    int sumOfSeries(int n) {
        int sum = (n * (n + 1)) / 2;
        return sum * sum;
    }
};

int main() {
    Solution sol;
    std::cout << sol.sumOfSeries(7) << std::endl;
    return 0;
}
