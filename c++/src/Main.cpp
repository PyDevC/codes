#include "Log.h"
#include <memory.h>

using namespace std;

int main(void) {
    int a = 10;
    int b = 1;
    int *ref = &a;
    Log(*ref);
    ref = &b;
    Log(++*ref);
  return 0;
}
