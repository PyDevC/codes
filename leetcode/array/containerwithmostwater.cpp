#include <vector>

using namespace std;
class Solution {
public:
  int maxArea(vector<int> &height) {
    int left = 0;
    int right = height.size() - 1;
    int area = 0;
    while (left < right) {
      int width = right - left;
      int length = min(height[left], height[right]);
      int temp = length * width;
      if (temp > area) {
        area = temp;
      } else if (height[left] < height[right]) {
        left++;
      } else {
        right--;
      }
    }
    return area;
  }
};
