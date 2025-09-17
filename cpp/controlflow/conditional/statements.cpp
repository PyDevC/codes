#include <iostream>

using namespace std;
int main(void) {
  int a = 10;
  if (a == 1) {
    cout << "Equal to one" << endl;
  } else if (a > 1) {
    cout << "Greater than one" << endl;
  } else {
    cout << "Less than one" << endl;
  }

  switch (a) {
  case 10:
    cout << "Equal to ten" << endl;
    break;
  case 1:
    cout << "Equal to one" << endl;
    break;
  default:
    cout << "Nothing special" << endl;
  }
}
