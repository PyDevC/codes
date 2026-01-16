#include "Log.h"
#include <memory.h>

using namespace std;

class Log {
private:
  int m_LogLevel;

public:
  enum { ERROR, WARN, TRACE } Levels;
  void SetLevel(int level) { m_LogLevel = level; }
  void Warn(const char *message) {
    if (m_LogLevel >= WARN)
      cout << "WARN: " << message << endl;
  }
  void Trace(const char *message) {
    if (m_LogLevel >= TRACE)
      cout << "TRACE: " << message << endl;
  }
  void Error(const char *message) {
    if (m_LogLevel >= ERROR)
      cout << "ERROR: " << message << endl;
  }
};

int main(void) {
  Log log;
  log.SetLevel(log.TRACE);
  log.Warn("This is warning");
  log.Error("This is error");
  log.Trace("This is tracing");
  return 0;
}
