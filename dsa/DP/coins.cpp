#include <climits>
#include <iostream>
#include <vector>

int getMinCoins(std::vector<int> &coins, int target) {
  std::vector<int> dp(target + 1, INT_MAX);
  dp[0] = 0;
  for (int i{1}; i <= target; ++i) {
    for (auto coin : coins) {
      if (coin <= i) {
        dp[i] = std::min(dp[i], dp[i - coin] + 1);
      }
    }
  }
  return dp[target] == INT_MAX ? -1 : dp[target];
}

int main() {
  std::vector<int> coins{};
  int target = 10;
  std::cout << getMinCoins(coins, target) << std::endl;
}
