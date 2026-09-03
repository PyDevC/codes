#include <bits/stdc++.h>
using namespace std;

class Solution {
private:
    inline int getStorage(int height, int width) {
        return height * width;
    }
public:
    int maxArea(vector<int>& height) {
        int leftWall{}, rightWall{static_cast<int>(height.size()) - 1};
        int maxStorage{};

        while(leftWall < rightWall) {
            maxStorage = std::max(maxStorage, getStorage(
                    /*height=*/std::min(height[leftWall], height[rightWall]), 
                    /*width=*/rightWall - leftWall));

            height[leftWall] < height[rightWall]? leftWall++ : rightWall--;
        }

        return maxStorage;
    }
};
