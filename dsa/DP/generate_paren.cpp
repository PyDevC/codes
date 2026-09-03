#include <bits/stdc++.h>
using namespace std;

void backtrace(int i, int j, int n, vector<string> &result, string &path) {
  if (i == n && j == n) {
    result.push_back(path);
    return;
  } else if (i > n || j > n) {
    return;
  }

  path.push_back('(');
  backtrace(i + 1, j, n, result, path);
  path.pop_back();
  if (j < i) {
    path.push_back(')');
    backtrace(i, j + 1, n, result, path);
    path.pop_back();
  }
}

vector<string> gen(int n) {
  vector<string> result{};
  string path = "(";
  backtrace(1, 0, n, result, path);
  return result;
}

int main() {
  int n = 3;
  auto out = gen(n);
  cout << "[";
  for (auto str : out) {
    cout << "\"" << str << "\", ";
  }
  cout << "]";
  return 0;
}
