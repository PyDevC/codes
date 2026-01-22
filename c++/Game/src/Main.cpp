#include "../../Engine/src/Engine.h"
#include <array>

using namespace engine;
int main(void) {
  Engine eng;
  eng.EchoVectorSpaceCoordinates();
  auto coord = eng.vs.GetVectorSpace();
  std::cout << coord << std::endl;
  std::array<int, 5> data;
  int size = data.size();
  std::cout << size << std::endl;
  return 0;
}
