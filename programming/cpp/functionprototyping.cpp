#include <iostream>

using namespace std;

void message(void);

int main() {
  cout << "This is the message" << endl;
  message();
  return 0;
}

void message(void) { cout << "The message is: close the program" << endl; }
