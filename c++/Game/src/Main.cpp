#include "../../Engine/src/Engine.h"
#include <algorithm>
#include <vector>

using namespace engine;
using namespace std;
int main(void) {
  std::vector<int> values = {1, 2, 3, 4, 5};
  auto it = std::find_if(values.begin(), values.end(),
                         [](int value) { return value > 3; });
  std::cout << *it << std::endl;
  return 0;
}
