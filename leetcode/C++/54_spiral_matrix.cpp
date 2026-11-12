#include <bits/stdc++.h>
using namespace std;

class Solution {
public:
    vector<int> spiralOrder(vector<vector<int>>& matrix) {
        int m = matrix.size();
        int n = matrix[0].size();

        int top = 0, bottom = m - 1, left = 0, right = n - 1;

        std::vector<int> spiral;
        spiral.reserve(m * n);

        while(top <= bottom && left <= right) {
            std::cout << top << " "<< bottom << " " << left << " " << right << std::endl;
            // left to right
            for(int i = left; i <= right; ++i) {
                spiral.push_back(matrix[top][i]);
            }
            ++top;

            // top to bottom
            for(int i = top; i <= bottom; ++i) {
                spiral.push_back(matrix[i][right]);
            }
            --right;

            // right to left
            if(top <= bottom) {
                for(int i = right; i >= left; --i) {
                    spiral.push_back(matrix[bottom][i]);
                }
                --bottom;
            }

            // bottom to top
            if(left <= right) {
                for(int i = bottom; i >= top; --i) {
                    spiral.push_back(matrix[i][left]);
                }
                ++left;
            }
        }

        return spiral;
    }
};

int main() {
    vector<vector<int>> matrix = {{1, 2, 3, 4}, {5, 6, 7, 8}, {9, 10, 11, 12}};
    Solution sol;
    auto out = sol.spiralOrder(matrix);
    for(auto o: out) {
        std::cout << o << " ";
    }
    std::cout << std::endl;
    return 0;
}

// follow up now instead of spiral do so that the property of spiral only holds for top and bottom and you have to capture all the elements from left to right in the order
