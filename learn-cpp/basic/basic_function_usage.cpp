#include <iostream>

using namespace std;

void line(), message(); // function prototypes

int main() {
  cout << "Hello World" << endl;
  line(); // user defined functions called
  message();
}

void line() { cout << "---------------------------------------" << endl; } // implementation of functions

void message() { cout << "message funciton" << endl; }
