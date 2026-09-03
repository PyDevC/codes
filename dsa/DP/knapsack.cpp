#include <iostream>
#include <vector>

int getMaxPrice(std::vector<std::pair<int, int>> &items, int weightThreshold) {
  int n = static_cast<int>(items.size());
  std::vector<std::vector<int>> dp(n + 1,
                                   std::vector<int>(weightThreshold + 1, 0));

  for (int i = 1; i < n + 1; ++i) {
    for (int j = 0; j < weightThreshold + 1; ++j) {
      if (items[i - 1].first > j) {
        dp[i][j] = dp[i - 1][j];
      } else {
        dp[i][j] = std::max(dp[i - 1][j], dp[i - 1][j - items[i - 1].first] +
                                              items[i - 1].second);
      }
    }
  }

  return dp[n][weightThreshold];
}

int main() {
  // Each pair represents {weight, price}
  std::vector<std::pair<int, int>> items = {{2, 12}, {3, 20}, {5, 45}};
  int weightThreshold{10};

  std::cout << "Max Possible Price: " << getMaxPrice(items, weightThreshold);
}
