// Problem Statement
// Given N Works which each take some tith amount of time to complete and gives
// s_ith amount of skills. You have to find out the gain maximum skill points in
// a given X time within only k amount of work.
#include <bits/stdc++.h>
using namespace std;

int backtrace(int item, int x, int k_left, std::vector<vector<int>> &works,
              std::vector<std::vector<std::vector<int>>> &dp) {
  if (k_left == 0 || x == 0) {
    return 0;
  }

  if (works[item][0] > x) {
    return 0;
  }
  // Cache
  if (dp[item][x][k_left] != -1) {
    return dp[item][x][k_left];
  }
    // Write checks and recursion to move to another decision
    // input in the cache the decision
    // return the max
}

// Get the max skill points for all the works
int maxSkillPoints(std::vector<vector<int>> &works, int x, int k) {
  std::vector<std::vector<std::vector<int>>> dp(
      k, std::vector<std::vector<int>>(x, std::vector<int>(works.size(), -1)));

  return backtrace(0, x, k, works, dp);
}

int main() {
  // Works {time, skill}
  std::vector<vector<int>> works = {{3, 4}, {2, 1}, {8, 9}};
  int xTime = 7;
  int kSlots = 2;
  std::cout << "Maximum Skill points: " << maxSkillPoints(works, xTime, kSlots);
}
