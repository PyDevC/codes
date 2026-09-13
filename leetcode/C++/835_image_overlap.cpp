#include <algorithm>
#include <iostream>
#include <vector>

class Solution {
  std::vector<std::vector<int>>
  applyingTransform(int r, int c, std::vector<std::vector<int>> &img1) {
    std::vector<std::vector<int>> result(img1.size(),
                                         std::vector<int>(img1.size(), 0));

    int n = img1.size();
    for (int i{}; i < n; ++i) {
      for (int j{}; j < n; ++j) {
        int nr = i + r;
        int nc = j + c;
        if ((nc >= 0 && nc < n) && (nr >= 0 && nr < n)) {
          result[nr][nc] = img1[i][j];
        }
        std::cout << result[i][j] << " ";
      }
      std::cout << std::endl;
    }

    std::cout << std::endl;
    return result;
  }

  int overlap(std::vector<std::vector<int>> img1,
              std::vector<std::vector<int>> &img2) {
    int result{};
    for (int i{}; i < img1.size(); ++i) {
      for (int j{}; j < img1.size(); ++j) {
        result += img1[i][j] & img2[i][j];
      }
    }

    return result;
  }

public:
  int largestOverlap(std::vector<std::vector<int>> &img1,
                     std::vector<std::vector<int>> &img2) {

    int maxOverlap{overlap(img1, img2)};
    int n = img1.size();
    for (int r = -(n - 1); r < n; ++r) {
      for (int c = -(n - 1); c < n; ++c) {
        maxOverlap =
            std::max(maxOverlap, overlap(applyingTransform(r, c, img1), img2));
      }
    }
    return maxOverlap;
  }
};

int main() {
  std::vector<std::vector<int>> img1 = {{0, 0, 0, 0, 1},
                                        {0, 0, 0, 0, 0},
                                        {0, 0, 0, 0, 0},
                                        {0, 0, 0, 0, 0},
                                        {0, 0, 0, 0, 0}};
  std::vector<std::vector<int>> img2 = {{0, 0, 0, 0, 0},
                                        {0, 0, 0, 0, 0},
                                        {0, 0, 0, 0, 0},
                                        {0, 0, 0, 0, 0},
                                        {1, 0, 0, 0, 0}};

  Solution sol;
  std::cout << sol.largestOverlap(img1, img2) << std::endl;
}
