/* The program below give error lets fix those errors
 *
 * #include <stream>
 * int main
 * {
 * cout << "If this text",
 * cout >> " appears on your display, ";
 * cout << " endl;"
 * cout << 'you can pat yourself on '
 * << " the back!"
 * << endl.
 * return 0;
 * )
 */

#include <iostream>

using namespace std;

int main() {
  cout << "If this text";
  cout << " appears on your display, " << endl;
  cout << "you can pat yourself on " << " the back!" << endl;
  return 0;
}
