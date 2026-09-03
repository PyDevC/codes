// Problem Statement
// Given N Works which each take some tith amount of time to complete and gives
// s_ith amount of skills. You have to find out the gain maximum skill points in
// a given X time within only k amount of work.

#include <iostream>
#include <vector>

int recSkillup(int index, int k_left, int x,
               std::vector<std::vector<int>> &workSlots) {
  if (index == workSlots.size() || k_left == 0 || x < 0) {
    return 0;
  }

  int skip = recSkillup(index + 1, k_left, x, workSlots);
  int time = workSlots[index][0];
  int skill = workSlots[index][1];
  int take{};
  if (x >= time) {
    take = skill + recSkillup(index + 1, k_left - 1, x - time, workSlots);
  }

  return std::max(skip, take);
}

int efficientSkillup(int x, int k, std::vector<std::vector<int>> &workSlots) {
  return recSkillup(0, x, k, workSlots);
}

int main() {
  // Slot is {time, skill}
  std::vector<std::vector<int>> workSlots = {{2, 3}, {3, 4}, {4, 5}, {1, 2}};
  std::cout << efficientSkillup(5, 2, workSlots) << std::endl;
  return 0;
}
