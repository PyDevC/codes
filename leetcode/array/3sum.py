from typing import List

class Solution:
    def threeSum(self, nums: List[int]) -> List[List[int]]:
        nums.sort()
        print(nums)
        output = []
        for i in range(len(nums) - 2):
            l = i + 1
            r = len(nums) - 1
            while l < r:
                print(i, l, r)
                print(nums[i] + nums[l] + nums[r])
                if (tsum:= nums[i] + nums[l] + nums[r]) == 0:
                    this = [nums[i], nums[l], nums[r]]
                    if this not in output:
                        output.append(this)
                    l += 1
                    r -= 1
                elif tsum > 0:
                    l += 1
                else:
                    r -= 1
                    
        return output

nums = [-100,-70,-60,110,120,130,160]
sol = Solution().threeSum(nums)
print(sol)
