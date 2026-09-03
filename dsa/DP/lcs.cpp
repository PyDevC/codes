#include <string>
#include <vector>

int findLCSLength(std::string &str1, std::string &str2) {
  std::vector<std::vector<int>> dp(str1.size() + 1,
                                   std::vector<int>(str2.size() + 1, 0));

  for (int i{1}; i < str1.size() + 1; ++i) {
    for (int j{1}; j < str2.size() + 1; ++j) {
      if (str1[i - 1] != str2[j - 1]) {
        dp[i][j] = std::max(dp[i - 1][j], dp[i][j - 1]);
      } else {
        dp[i][j] = dp[i - 1][j - 1] + 1;
      }
    }
  }
  return dp[str1.size()][str2.size()];
}
