#include <stdio.h>

int main() {
  int x = 10;
  int *ptr = &x;
  printf("Address of x %p", ptr);
  printf("Value of x %d", x);
  return 0;
}
