#include "../../Engine/src/Engine.h"

using namespace engine;
int main(void) {
  Engine eng;
  eng.EchoVectorSpaceCoordinates();
  auto coord = eng.vs.GetVectorSpace();
  std::cout << coord << std::endl;
  return 0;
}
