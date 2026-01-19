#include <iostream>

using String = std::string;

class Entity {
private:
  String m_Name;

public:
  Entity() : m_Name("Unknown") {}
  Entity(const String &name) : m_Name(name) {}
  const String &GetName() const { return m_Name; }
};

int main(void) {
  Entity e = Entity("Entity");
  std::cout << e.GetName() << std::endl;

  Entity *eh = new Entity[50]();
  std::cout << eh->GetName() << std::endl;

  Entity &reff = e;
  std::cout << reff.GetName() << std::endl;

  delete[] eh;
  return 0;
}
