#include <iostream>
#include "Log.h"

using namespace std;

void Log(const char* message){
    cout << message << endl;
}

int main() {
    InitLog();
    Log("Hey!");
  return 0;
}
