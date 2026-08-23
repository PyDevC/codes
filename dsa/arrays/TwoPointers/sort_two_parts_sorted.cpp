#include "helper.hpp"

class Solution {
public:
  void sortHalves(std::vector<int> &arr) {
    int secondIndex{-1};
    int n = static_cast<int>(arr.size());

    for (int i{}; i < n - 1; ++i) {
      if (arr[i] > arr[i + 1]) {
        secondIndex = i;
        break;
      }
    }

    if (secondIndex == -1) {
      return;
    }

    std::vector<int> tempArr(n);
    int i{};
    int left{}, right{secondIndex + 1};
    while (left <= secondIndex && right < n) {
      if (arr[left] <= arr[right]) {
        tempArr[i] = arr[left];
        left++;
        i++;
      } else if (arr[left] > arr[right]) {
        tempArr[i] = arr[right];
        right++;
        i++;
      }
    }

    while (left <= secondIndex) {
      tempArr[i] = arr[left];
      i++;
      left++;
    }
    while (right < n) {
      tempArr[i] = arr[right];
      i++;
      right++;
    }

    std::swap(arr, tempArr);
  }
};

int main() {
  std::vector<int> arr{5, 4, 7, 10, 10, 12};

  Solution sol;
  sol.sortHalves(arr);
  printVector(arr);

  return 0;
}
