#include <iostream>
using namespace std;

class Entity {
public:
  virtual std::string GetName() { return "Entity"; }
  float X, Y;
  void Move(float xa, float ya) {
    X += xa;
    Y += ya;
  }

  void Print() { cout << "X: " << X << "\nY: " << Y << endl; }
};

class Player : public Entity {
private:
  std::string m_Name;

public:
  float speed;
  Player(const std::string &name) : m_Name(name) {}
  std::string GetName() override { return m_Name; }
  void Move(float xa, float ya) {
    X += (xa * speed);
    Y += (ya * speed);
  }
};

void PrintName(Entity *entity) { cout << entity->GetName() << endl; }

int main(void) {

  Entity *e = new Entity();
  PrintName(e);
  Player *p = new Player("Player");
  cout << p->GetName() << endl;
  PrintName(p);
  return 0;
}
