#include <iomanip>
#include <iostream>
using namespace std;

int main() {
  int x, y;
  cin >> x >> y;

  int p = x + y;
  int q = x - y;
  int r = x * y;

  float s{};
  if (y == 0) {
    s = 0.0f;
  } else {
    s = float(x) / y;
  }

  int t = x / y;
  int u = x % y;

  cout << p << " " << q << " " << r << " " << fixed << setprecision(3) << s
       << " " << t << " " << u;

  return 0;
}
