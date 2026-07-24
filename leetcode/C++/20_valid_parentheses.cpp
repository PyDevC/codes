#include <iostream>
#include <stack>

class Solution {
private:
  bool isOpen(char paren) {
    switch (paren) {
    case '(':
    case '{':
    case '[':
      return true;
    default:
      return false;
    };
  }

  char opening(char close) {
    switch (close) {
    case '}':
      return '{';
    case ')':
      return '(';
    case ']':
      return '[';
    default:
      return ' ';
    }
  }

public:
  bool isValid(std::string s) {
    if (s.empty() || s[0] == ')' || s[0] == '}' || s[0] == ']') {
      return false;
    }

    std::stack<char> parenStack{};
    for (auto paren : s) {
      if (isOpen(paren)) {
        parenStack.push(paren);
      } else {
        if (!parenStack.empty() && parenStack.top() == opening(paren)) {
          parenStack.pop();
        } else {
          return false;
        }
      }
    }
    return parenStack.empty();
  }
};

int main() {
  std::string s = "{{[]}{}{}}";
  Solution sol;
  std::cout << sol.isValid(s);
  return 0;
}
