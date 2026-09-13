#include <iostream>
#include <queue>
#include <vector>

class Solution {
  std::vector<std::vector<int>>
  getGraph(int numCourses, std::vector<std::vector<int>> &prerequisites) {
    std::vector<std::vector<int>> graph(numCourses, std::vector<int>());
    for (int i{}; i < prerequisites.size(); ++i) {
      graph[prerequisites[i][1]].push_back(prerequisites[i][0]);
    }
    return graph;
  }

public:
  std::vector<int> findOrder(int numCourses,
                             std::vector<std::vector<int>> &prerequisites) {
    std::vector<int> result{};
    std::vector<int> indegree(numCourses, 0);
    std::queue<int> nodeQueue{};
    auto graph = getGraph(numCourses, prerequisites);

    // indegree of each node
    for (auto &node : graph) {
      for (int adjecent : node) {
        indegree[adjecent]++;
      }
    }

    for (int i{}; i < numCourses; ++i) {
      if (indegree[i] == 0) {
        nodeQueue.push(i);
      }
    }

    while (!nodeQueue.empty()) {
      auto curr = nodeQueue.front();
      nodeQueue.pop();
      result.push_back(curr);
      for (auto &node : graph[curr]) {
        indegree[node]--;
        if (indegree[node] == 0) {
          nodeQueue.push(node);
        }
      }
    }

    return result;
  }
};

int main() {
  std::vector<std::vector<int>> prerequisites = {
      {3, 0}, {3, 1}, {3, 2}, {3, 4}, {5, 4}};
  int numCourses = 6;
  Solution sol;
  auto answer = sol.findOrder(numCourses, prerequisites);
  for (auto ans : answer) {
    std::cout << ans << std::endl;
  }
  return 0;
}
