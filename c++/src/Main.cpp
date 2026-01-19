#include <iostream>

using String = std::string;

class Entity {
private:
  String m_Name;
  int m_Age;

public:
  Entity() : m_Name("Unknown") {}
  Entity(const String &name) : m_Name(name) {}
  Entity(int age) : m_Age(age) {}
  const String &GetName() const { return m_Name; }
  int GetAge() const { return m_Age; }
};

void PrintEntity(const Entity &entity) {
  std::cout << entity.GetName() << std::endl;
  std::cout << entity.GetAge() << std::endl;
}

int main(void) {
  Entity e = Entity("Entity");
  PrintEntity(e);
  PrintEntity(11);
  return 0;
}
