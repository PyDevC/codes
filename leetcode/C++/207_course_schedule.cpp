#include <iostream>
#include <vector>

class Solution {
  bool dfs(int node, std::vector<std::vector<int>> &prerequisites,
           std::vector<bool> &visited, std::vector<bool> &rec) {
    if (rec[node]) {
      return false;
    }
    if (visited[node]) {
      return true;
    }

    visited[node] = true;
    rec[node] = true;

    for (const auto &pair : prerequisites) {
      if (pair[1] == node) {
        if (!dfs(pair[0], prerequisites, visited, rec)) {
          return false;
        }
      }
    }

    rec[node] = false;
    return true;
  }

public:
  bool canFinish(int numCourses, std::vector<std::vector<int>> &prerequisites) {
    std::vector<bool> visited(numCourses, false);
    std::vector<bool> rec(numCourses, false);
    for (int i{}; i < numCourses; ++i) {
      if (!visited[i] && !dfs(i, prerequisites, visited, rec)) {
        return false;
      }
    }
    return true;
  }
};

int main() {
  Solution sol;
  std::vector<std::vector<int>> prerequisites = {
      {1, 0}, {2, 0}, {3, 1}, {3, 2}};
  std::cout << sol.canFinish(4, prerequisites) << std::endl;
  return 0;
}
