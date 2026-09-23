#include <bits/stdc++.h>
using namespace std;

vector<int> lis(std::vector<int> &nums) {
  int n = nums.size();
  std::vector<int> currLis{};
  std::vector<int> inserted(n, -1);
  for (int i{}; i < n; ++i) {
    if (currLis.empty() || currLis.back() < nums[i]) {
      currLis.push_back(nums[i]);
      inserted[i] = currLis.size();
    } else {
      auto it = lower_bound(currLis.begin(), currLis.end(), nums[i]);
      *it = nums[i];
      inserted[i] = it - currLis.begin() + 1;
    }
  }

  int currlen = currLis.size();
  for (int i{n - 1}; i >= 0; --i) {
    if (inserted[i] == currlen) {
      currLis[currlen - 1] = nums[i];
      --currlen;
    }
  }

  return currLis;
}

int main() {
  std::vector<int> nums = {1, 5, 7, 10, 9, 6, 7, 9, 2, 3};
  auto answer = lis(nums);
  cout << "[";
  for (auto ans : answer) {
    cout << ans << " ";
  }
  cout << "\b]" << endl;
  return 0;
}
