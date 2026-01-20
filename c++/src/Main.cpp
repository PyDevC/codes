#include <iostream>
#include <vector>

struct Vertex {
  float x, y, z;
};

std::ostream &operator<<(std::ostream &stream, const Vertex &vertex) {
  stream << vertex.x << ", " << vertex.y << ", " << vertex.z;
  return stream;
}

int main(void) {
  Vertex *vertex = new Vertex[5];
  vertex[0].x = 10;
  vertex[0].y = 10;
  vertex[0].z = 10;
  std::cout << vertex[0] << std::endl;
  std::vector<Vertex> vec1;
  vec1.push_back({10, 10, 10});
  vec1.push_back({11, 10, 10});
  vec1.push_back({12, 10, 10});
  vec1.push_back({13, 10, 10});
  vec1.push_back({14, 10, 10});
  vec1.erase(vec1.begin() + 1);
  for (Vertex &v : vec1)
    std::cout << v << std::endl;
  vec1.clear();
  return 0;
}
