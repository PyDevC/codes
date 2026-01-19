#include <iostream>

class Entity {
public:
  int Age;
  Entity() { std::cout << "Created" << std::endl; }
  ~Entity() { std::cout << "Destroyed" << std::endl; }
};

class scopedPtr {
private:
  Entity *m_ptr;

public:
  scopedPtr(Entity *ptr) : m_ptr(ptr) {}
  ~scopedPtr() { delete m_ptr; }
};

int main(void) {
  {
    scopedPtr s = new Entity();
    scopedPtr e(new Entity());
  }
  return 0;
}
