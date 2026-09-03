#include <bits/stdc++.h>
using namespace std;

class Solution {
  void backtrace(int i, int target, vector<int> &candidates,
                 vector<vector<int>> &result, vector<int> &path) {
    if (target == 0) {
      result.push_back(path);
      return;
    } else if (target < 0 || i == candidates.size()) {
      return;
    }

    path.push_back(candidates[i]);
    backtrace(i, target - candidates[i], candidates, result, path);
    path.pop_back();
    backtrace(i + 1, target, candidates, result, path);
  }

public:
  vector<vector<int>> combinationSum(vector<int> &candidates, int target) {
    vector<vector<int>> result{};
    vector<int> path{};
    backtrace(0, target, candidates, result, path);
    return result;
  }
};
