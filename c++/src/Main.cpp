#include <cstring>
#include <iostream>

class String {
private:
  char *m_Buffer;
  unsigned int m_Size;

public:
  String(const char *string) {
    m_Size = strlen(string);
    m_Buffer = new char[m_Size + 1];
    std::memcpy(m_Buffer, string, m_Size);
  }
  friend std::ostream &operator<<(std::ostream &stream, const String &string);
};

std::ostream &operator<<(std::ostream &stream, const String &string) {
  stream << string.m_Buffer;
  return stream;
}

int main(void) {
  String string = "Test";
  std::cout << string << std::endl;
  return 0;
}
