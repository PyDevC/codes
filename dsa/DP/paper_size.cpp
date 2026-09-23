// Problem Statement
// Given a Paper of size M x N you have to cut it k times.
// After K cuts, each will have penalty = sum(Area_i**2) where Area_i is area of
// each final cut. Find the minimum penalty
#include <iostream>

int penalty(int n, int m) { return (n * m) * (n * m); }

int minPenalty(int n, int m, int k) {
  if (k == 0 || (n == 1 && m == 1)) {
    return penalty(m, n);
  }

  int min = minPenalty(n, m, k - 1);
  for (int h{1}; h < n; ++h) {
    for (int c{}; c < k; ++c) {
      int pen = minPenalty(h, m, c) + minPenalty(n - h, m, k - 1 - c);
      min = std::min(min, pen);
    }
  }

  for (int h{1}; h < n; ++h) {
    for (int c{}; c < k; ++c) {
      int pen = minPenalty(n, h, c) + minPenalty(n, m - h, k - 1 - c);
      min = std::min(min, pen);
    }
  }
  return min;
}

int main() {
  int n{5};
  int m{3};
  int k{2};
  std::cout << minPenalty(n, m, k) << std::endl;
}
