#include "../../Engine/src/Engine.h"
template <typename T> void Print(T value) { std::cout << value << std::endl; }

int main(void) {
  engine::Engine engine;
  engine.EchoVectorSpaceCoordinates();
  Print<int>(10);
  Print<std::string>("Game Engine");
  Print<float>(4.4f);
  Print<double>(4.234);
  return 0;
}
