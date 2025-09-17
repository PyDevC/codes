#include <iostream>

using namespace std;
int main(void) {
  int i;

  for (i = 0; i < 10; i++) {
    cout << i << endl;
  }

  while (i < 20) {
    cout << i << endl;
    i++;
  }

  do {
    cout << i << endl;
    i++;
  } while (i < 30);
}
