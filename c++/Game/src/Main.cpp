#include <iostream>

class Base {
public:
  Base() { std::cout << "Base Constructor\n"; }
  virtual ~Base() { std::cout << "Base Destructor\n"; }
};

class Derived : public Base {
public:
  Derived() { std::cout << "Derived Constructor\n"; }
  ~Derived() { std::cout << "Derived Destructor\n"; }
};

int main(void) {
  Base *base = new Base();
  delete base;
  std::cout << "----------------------------------\n";
  Derived *derived = new Derived();
  delete derived;
  Base *poly = new Derived();
  delete poly;

  double value = 4.55;
  double s = static_cast<int>(value) + 5.3;
  std::cout << s << std::endl;
  return 0;
}
