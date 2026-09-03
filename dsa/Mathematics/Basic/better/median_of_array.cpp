// Original (../median_of_array.cpp) computed correct VALUES but:
//   1. Took a mutable reference and sorted the CALLER'S vector in place - a
//      surprising side effect for a read-only query named findMedian.
//   2. Returned the magic value 0 for empty input, indistinguishable from a
//      genuine median; throwing is honest.
//   3. Full sort is O(n log n). std::nth_element places just the element that
//      belongs at index mid in O(n) average time; for even sizes only one more
//      pass (max of the lower half) is needed.
#include <algorithm>
#include <cstddef>
#include <iostream>
#include <stdexcept>
#include <vector>

class Solution {
public:
  double findMedian(const std::vector<int> &arr) { // const&: no mutation
    if (arr.empty()) {
      throw std::invalid_argument("findMedian: empty array");
    }

    const std::size_t mid = arr.size() / 2;
    std::vector<int> work(arr); // operate on a copy, caller keeps its order

    std::nth_element(work.begin(), work.begin() + static_cast<long>(mid),
                     work.end());
    // work[mid] is now exactly the fully sorted order statistic at `mid`;
    // everything before it is <= it (in arbitrary internal order).
    const int upper = work[mid];

    if (arr.size() % 2 == 1) {
      return upper;
    }
    const int lower =
        *std::max_element(work.begin(), work.begin() + static_cast<long>(mid));
    return (static_cast<double>(lower) + upper) / 2.0; // explicit double math
  }
};

int main() {
  Solution sol;
  std::vector<int> arr{1, 2};
  std::cout << sol.findMedian(arr) << '\n';              // 1.5
  std::vector<int> odd{5, 3, 1, 4, 2};
  std::cout << sol.findMedian(odd) << '\n';              // 3
  std::cout << "caller untouched: " << arr[0] << arr[1] << '\n'; // 12 (was sorted)
  return 0;
}
