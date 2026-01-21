#include "Engine.h"

namespace engine {
using namespace engine;

Engine::VectorSpace::VectorSpace() : m_coordinates({}) {}

Engine::VectorSpace::VectorSpace(Engine::VectorSpace::Coordinates &coor)
    : m_coordinates(coor) {}

Engine::VectorSpace::Coordinates Engine::VectorSpace::GetVectorSpace() {
  return m_coordinates;
}

void Engine::VectorSpace::SetCoordinates(
    Engine::VectorSpace::Coordinates &coor) {
  m_coordinates = coor;
}

std::ostream &operator<<(std::ostream &stream, const Vector3 &vector3) {
  stream << "[" << vector3.X << ", " << vector3.Y << ", " << vector3.Z << "]";
  return stream;
}
std::ostream &operator<<(std::ostream &stream,
                         const Engine::VectorSpace::Coordinates &coor) {
  stream << "Coordinates {" << coor.start << "," << coor.end << "}";
  return stream;
}

void Engine::EchoVectorSpaceCoordinates() {
  std::cout << vs.GetVectorSpace() << std::endl;
}

} // namespace engine
