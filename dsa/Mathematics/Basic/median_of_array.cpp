#include <algorithm>
#include <iostream>
#include <vector>

class Solution {
public:
  double findMedian(std::vector<int> &arr) {
    if (arr.empty())
      return 0;

    // The only way I could think of
    std::sort(arr.begin(), arr.end());
    int n = static_cast<int>(arr.size());
    if (n % 2 == 0) {
      return static_cast<double>(arr[n / 2] + arr[(n / 2) - 1]) / 2;
    } else {
      return arr[n / 2];
    }
  }
};

int main() {
  std::vector<int> arr{1, 2};
  Solution sol;
  std::cout << sol.findMedian(arr) << std::endl;
}
