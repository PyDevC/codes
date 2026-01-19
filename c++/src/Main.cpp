#include <iostream>

struct Vector2 {
  float x, y;
  Vector2(float x, float y) : x(x), y(y) {}
  Vector2 Add(const Vector2 &other) const {
    return Vector2(x + other.x, y + other.y);
  }
  Vector2 Multiply(const Vector2 &other) const {
    return Vector2(x * other.x, y * other.y);
  }
  Vector2 operator+(const Vector2 &other) const {
    return Vector2(x + other.x, y + other.y);
  }
  Vector2 operator*(const Vector2 &other) const {
    return Vector2(x * other.x, y * other.y);
  }
  bool operator==(const Vector2 &other) const {
    return other.x == x && other.y == y;
  }
  bool operator!=(const Vector2 &other) const { return !(*this == other); }
};

std::ostream &operator<<(std::ostream &stream, const Vector2 &other) {
  stream << other.x << ", " << other.y;
  return stream;
}

int main(void) {
  Vector2 position(4.0f, 5.0f);
  Vector2 speed(4.0f, 5.0f);
  Vector2 result1 = position + speed;
  Vector2 result2 = position * speed;
  std::cout << result1 << std::endl;
  if (result1 == result2) {
    std::cout << result2 << std::endl;
  } else {
    std::cout << "Not" << std::endl;
  }
  return 0;
}
