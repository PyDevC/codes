#pragma once

#include <iostream>
#define DEBUG_ENGINE 0

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
  Engine() {}

  VectorSpace vs;
  void EchoVectorSpaceCoordinates();

#ifdef DEBUG_ENGINE
  class Logger {
  public:
    enum {
      LogWarning,
      LogError,
      LogTrace,
    } LogLevel;

  private:
        long int m_Size;
  public:
    Logger() {}
    ~Logger() {}
  };
#endif // DEBUG_ENGINE
};

} // namespace engine
