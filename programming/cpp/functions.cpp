// I am familiar with most of the content in cpp about funciton declaration so
// I skip this part for others to make a pull request
//
// Calculate the power of a number

#include <cmath>
#include <cstdint>
#include <iostream>

using namespace std;
void getpower_tentoten() {
  // Declaring variables
  double_t power;
  double_t base;

  // initializing the variables
  power = 10.0;
  base = 10.0;

  cout << "value of " << base << " to the power of " << power << " is "
       << pow(base, power) << endl;
}

int main(void) {
  getpower_tentoten();
  return 0;
}
