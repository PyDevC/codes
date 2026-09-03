#include <bits/stdc++.h>
using namespace std;

void backtrace(int i, vector<int> &nums, vector<vector<int>> &result) {
  if (i == nums.size()) {
    result.push_back(nums);
    return;
  }

  for (int j{i}; j < nums.size(); ++j) {
    swap(nums[i], nums[j]);
    backtrace(i + 1, nums, result);
    swap(nums[i], nums[j]);
  }
}

vector<vector<int>> permute(vector<int> &nums) {
  vector<vector<int>> result{};
  backtrace(0, nums, result);
  return result;
}

int main() {
  vector<int> nums = {1, 2, 3};
  auto out = permute(nums);
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
