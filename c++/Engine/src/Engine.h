#pragma once

#include <iostream>

namespace engine {
struct Vector3 {
  // Vector to represent 3D coordinates
  float X;
  float Y;
  float Z;
};

class Engine {
public:
  class VectorSpace {
  public:
    struct Coordinates {
      Vector3 start;
      Vector3 end;
    };

  private:
    Coordinates m_coordinates;

  public:
    VectorSpace();
    VectorSpace(Coordinates &coor);
    Coordinates GetVectorSpace();
    void SetCoordinates(Coordinates &coor);
    friend std::ostream &operator<<(std::ostream &stream,
                                    const Coordinates &coor);
    friend std::ostream &operator<<(std::ostream &stream, const Vector3 &coor);
  };

  VectorSpace vs;
  void EchoVectorSpaceCoordinates();
};

} // namespace engine
