#include <bits/stdc++.h>
using namespace std;

void backtrace(int i, vector<int> &nums, vector<int> &path,
               vector<vector<int>> &result) {
  if (i == nums.size()) {
    result.push_back(path);
    return;
  }

  // take
  path.push_back(nums[i]);
  backtrace(i + 1, nums, path, result);

  // Skip
  path.pop_back();
  backtrace(i + 1, nums, path, result);
}

vector<vector<int>> subsets(vector<int> &sets) {
  vector<vector<int>> result{};
  vector<int> paths{};
  backtrace(0, sets, paths, result);
  return result;
}

int main() {
  vector<int> set = {1, 2, 3};
  auto subset = subsets(set);

  cout << "[";
  for (auto set : subset) {
    cout << "[";
    for (auto s : set) {
      cout << s << ", ";
    }
    cout << "], ";
  }
  cout << "]";
}
