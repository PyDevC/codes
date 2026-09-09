#include <bits/stdc++.h>
using namespace std;

class Solution {
public:
  void merge(vector<int> &nums1, int m, vector<int> &nums2, int n) {
    if (n == m) {
      if (nums1[m - 1] == 0) {
        return;
      }
    }

    int insertIndex{m};
    if (m == 0) {
      copy(nums2.begin(), nums2.end(), nums1.begin());
    }

    // insertion sort
    for (int i{}; i < n; ++i) {
      // Add the element to the new array
      nums1[insertIndex] = nums2[i];
      int j = insertIndex;
      while (nums1[j - 1] > nums1[j]) {
        swap(nums1[j - 1], nums1[j]);
        --j;
      }
      insertIndex++;
    }
  }
};
