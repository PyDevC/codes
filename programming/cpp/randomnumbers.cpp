#include <cstdint>
#include <cstdlib>
#include <iostream>
#include <random>

using namespace std;
int main(void) {
  // Simple random number generation
  cout << std::rand() << endl;

  // Cryptographic secure random number generation
  // (depends on acutal uncertainities such as device anomalies. Thus, slower)
  uint8_t seed = 10;
  random_device rd;
  cout << rd() << endl;
  // There are many variation of doing this
}
