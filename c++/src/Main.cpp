#include <iostream>
#include <memory>

class Entity {
public:
  int Age;
  Entity() { std::cout << "Created" << std::endl; }
  ~Entity() { std::cout << "Destroyed" << std::endl; }
  void Print() { std::cout << "Print" << std::endl; }
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
    std::unique_ptr<Entity> entity = std::make_unique<Entity>();
    std::shared_ptr<Entity> entity1 = std::make_shared<Entity>();
    std::shared_ptr<Entity> entity2 = entity1;
    std::shared_ptr<Entity> entity3 = entity1;
    std::shared_ptr<Entity> entity4 = entity2;
    std::shared_ptr<Entity> entity5 = entity1;
    entity->Print();
    entity1->Print();
    entity2->Print();
    entity3->Print();
    entity4->Print();
    entity5->Print();
  }
  return 0;
}
