#include <bits/stdc++.h>
using namespace std;

void backtrace(int i, int target, vector<int> &nums,
               vector<vector<int>> &result, vector<int> &path) {
  if (target == 0) {
    result.push_back(path);
    return;
  }

  if (target < 0 || i == nums.size()) {
    return;
  }

  path.push_back(nums[i]);
  backtrace(i, target - nums[i], nums, result, path);
  path.pop_back();
  backtrace(i + 1, target, nums, result, path);
}

vector<vector<int>> combination_sum(vector<int> &nums, int target) {
  vector<vector<int>> result{};
  vector<int> path{};
  backtrace(0, target, nums, result, path);
  return result;
}

int main() {
  vector<int> nums = {2, 3, 5};
  auto out = combination_sum(nums, 8);
  cout << "[";
  for (auto arr : out) {
    cout << "[";
    for (auto s : arr) {
      cout << s << ", ";
    }
    cout << "], ";
  }
  cout << "]";
  return 0;
}
