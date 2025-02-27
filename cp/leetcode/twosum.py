class Solution:
    def twoSum(self, nums: List[int], target: int) -> List[int]:
        for i in range(len(nums)):
            x = []
            comp = target - nums[i]
            if len(x) != 0 and comp != x[i]:
                x.append(comp)
        
