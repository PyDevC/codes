// Original issues (../add_two_numbers.cpp):
//   1. `t = x / y` and `u = x % y` were evaluated even when y == 0, which is
//      undefined behaviour (usually SIGFPE). Only the float division `s` was
//      guarded, so the guard did not actually protect the program.
//   2. `using namespace std;` dumps the whole std namespace into scope; dropped.
//   3. `float(x) / y` computes in float (~7 significant digits); double is the
//      default floating type in C++ and avoids needless precision loss.
#include <iomanip>
#include <iostream>

int main() {
  int x{}, y{};
  if (!(std::cin >> x >> y)) {
    std::cerr << "expected two integers\n";
    return 1;
  }

  const int p = x + y;
  const int q = x - y;
  const int r = x * y; // NOTE: overflows like the original; output type is int

  // FIX: guard *all* divisions/modulos by y, not just the floating-point one.
  double s = 0.0;
  int t = 0;
  int u = 0;
  if (y != 0) {
    s = static_cast<double>(x) / y;
    t = x / y;
    u = x % y;
  }
  // NOTE: when y == 0 the true quotient/remainder do not exist; we emit 0s
  // solely to keep the six-field output format intact (the original crashed).

  std::cout << p << ' ' << q << ' ' << r << ' '
            << std::fixed << std::setprecision(3) << s << ' ' << t << ' '
            << u << '\n';
  return 0;
}
