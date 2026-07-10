from typing import List

class Solution:
    def twoSum(self, nums: List[int], target: int) -> List[int]:
        cache = {}
        for i in range(len(nums)):
            comp = target - nums[i]
            if nums[i] in cache:
                return [cache[nums[i]], i]

            cache[comp] = i
        return []

sol = Solution()
nums = [2,7,11,15]
target = 9
print(sol.twoSum(nums, target))
