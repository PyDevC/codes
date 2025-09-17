#include <iostream>

using namespace std;
int main() {
  int i;

  for (i = 0; i < 10; i++) {
    if (i == 1) {
      continue;
    }
    if (i == 9) {
      break;
    }
    cout << i << endl;
  }
}
