#include <bits/stdc++.h>
using namespace std;

class Solution {
public:
    double findMedianSortedArrays(vector<int>& nums1, vector<int>& nums2) {
        int n = static_cast<int>(nums1.size());
        int m = static_cast<int>(nums2.size());

        int length = n + m;
        std::vector<int> nums(length, 0);

        int i = 0, j = 0, k = 0;

        while(i < n && j < m) {
            if(nums1[i] < nums2[j]) {
                nums[k] = nums1[i];
                ++i;
            } else {
                nums[k] = nums2[j];
                ++j;
            }
            ++k;
        }

        while(i < n){
            nums[k] = nums1[i];
            ++i;
            ++k;
        }

        while(j < m){
            nums[k] = nums2[j];
            ++j;
            ++k;
        }

        double result{};
        if (length % 2 == 0) {
            result = (static_cast<double>(nums[(length / 2) - 1]) + static_cast<double>(nums[length / 2])) / 2;
        } else {
            result = static_cast<double>(nums[(length / 2)]);
        }

        return result;
    }
};

int main() {
    Solution sol;
    std::vector<int> nums1 = {1, 3};
    std::vector<int> nums2 = {2, 4};
    std::cout << sol.findMedianSortedArrays(nums1, nums2);
    return 0;
}
