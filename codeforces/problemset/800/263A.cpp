#include <iostream>

void minMoves(int &i, int &j) {
  while (j <= 5) {
    i = 1;
    while (i <= 5) {
      int value{};
      std::cin >> value;
      if (value == 1) {
        return;
      }
      i++;
    }
    j++;
  }
}

int main() {
  std::ios_base::sync_with_stdio(false);
  std::cin.tie(NULL);

  int i{1}, j{1};
  minMoves(i, j);
  std::cout << std::abs(i - 3) + std::abs(j - 3) << std::endl;
  return 0;
}
