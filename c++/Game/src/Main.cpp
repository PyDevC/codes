#include "../../Engine/src/Engine.h"
#include <functional>
#include <vector>

void Hello() { std::cout << "Hello" << std::endl; }

void PrintValue(int value) { std::cout << value << std::endl; }

void forevery(const std::vector<int> &values,
              const std::function<void(int)> &func) {
  for (int value : values) {
    func(value);
  }
}

using namespace engine;
int main(void) {
  Engine eng;
  eng.EchoVectorSpaceCoordinates();
  auto coord = eng.vs.GetVectorSpace();
  std::cout << coord << std::endl;
  int a = 5;

  void (*hellofunction)(); // ok this is something amazing Can I use it in c
  hellofunction = Hello;   // Syntax is type(*variablename)(parameter);
  hellofunction();

  auto function = Hello; // Simplistic way to write function pointer
  function();
  auto lambda = [=](int value) { std::cout << value + a << std::endl; };
  std::vector<int> values = {1, 2, 3, 4, 5};
  forevery(values, lambda);
  return 0;
}
