// Original issues (../closest_to_n_divisible_by_m.cpp):
//   1. n == 0 returned `m`, but the multiple of m closest to 0 is 0 itself.
//   2. The comparator compared SIGNED gaps: (n - first) vs (n - second). The
//      two candidates always sit on opposite sides of n, so one gap is the
//      negation of the other; for positive n the branch
//      `(n - first) < (n - second)` is therefore always false and std::max
//      blindly returns `first`, ignoring actual distances: it answered
//      12 where 15 was expected for (n=14, m=3).
//   3. For negative n the same signed comparison picks the SMALLER candidate:
//      (-15, 6) printed -18 although -12 is equidistant and greater.
//   4. Its tie-break `abs(first) > abs(second)` only coincides with the GFG
//      rule ("on a tie return the greater number") for positive candidates;
//      for n = -2, m = 4 it would return -4 instead of 0.
//   Distances must be compared with std::abs(); then a plain max/min handles
//   every case without std::max's comparator subtleties.
#include <algorithm>
#include <cstdlib>
#include <iostream>

class Solution {
public:
  int closestNumber(int n, int m) {
    const int q = n / m;   // C++ division truncates toward zero,
    const int cand1 = q * m; // so cand1 is the adjacent multiple on that side.

    const int step = std::abs(m);
    // Step away from cand1 to its neighbouring multiple, in whichever
    // direction reaches past n.
    const int cand2 = (cand1 <= n) ? cand1 + step : cand1 - step;

    const int dist1 = std::abs(n - cand1); // distances MUST be unsigned gaps
    const int dist2 = std::abs(n - cand2);

    if (dist1 < dist2)
      return cand1;
    if (dist2 < dist1)
      return cand2;
    return std::max(cand1, cand2); // equidistant -> greater one (GFG rule)
  }
};

int main() {
  Solution sol;
  std::cout << sol.closestNumber(10, 3) << '\n';   //  9
  std::cout << sol.closestNumber(14, 3) << '\n';   // 15 (original gave 12)
  std::cout << sol.closestNumber(13, 4) << '\n';   // 12
  std::cout << sol.closestNumber(-15, 6) << '\n';  // -12 (original gave -18)
  std::cout << sol.closestNumber(-2, 4) << '\n';   //  0  (tie -> greater)
  std::cout << sol.closestNumber(0, 7) << '\n';    //  0  (original gave 7)
  return 0;
}
