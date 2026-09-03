#include <iostream>
#include <vector>
#include <cassert>
#include <algorithm>

class Solution {
public:
    long long findKthSmallest(std::vector<int>& coins, int k) {
        std::sort(coins.begin(), coins.end());
        int idx{};
        int i{};

        while (idx < k) {
            int curr = coins[i];
            while(curr < coins[i + 1]) {
            }
        }
    }
};

int main() {
    std::vector<int> coins = {3, 6, 9};
    int k{3};
    Solution sol;
    assert(sol.findKthSmallest(coins, k) == 10);
    return 0;
}
