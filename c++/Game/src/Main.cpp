#include <chrono>
#include <iostream>
#include <string>

struct Timer {
public:
  std::chrono::time_point<std::chrono::high_resolution_clock> start, end;
  std::chrono::duration<float> duration;

  Timer() { start = std::chrono::high_resolution_clock::now(); }
  ~Timer() {
    end = std::chrono::high_resolution_clock::now();
    duration = end - start;
    float ms = duration.count() * 1000.0f;
    std::cout << ms << " ms";
  }
};

void Function() {
  Timer timer;
  int a;
  for (int i = 0; i < 1000000; i++) {
    a = 10;
  }
  std::cout << a << std::endl;
}

int main(void) {
  Function();
  return 0;
}
