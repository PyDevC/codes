import math

class Solution:
    def findMedianSortedArrays(self, nums1, nums2):
        n = len(nums1)
        m = len(nums2)
        nums = []

        i, j = 0, 0

        while i < n and j < m:
            if nums1[i] < nums2[j]:
                nums.append(nums1[i])
                i += 1
            else:
                nums.append(nums2[j])
                j += 1

        if i < n:
            nums.extend(nums1[i:])

        if j < m:
            nums.extend(nums2[j:])

        length = m + n
        if length % 2 == 0:
            return (nums[length // 2 - 1] + nums[length // 2]) / 2
        else:
            return float(nums[length // 2])



sol = Solution()
print(sol.findMedianSortedArrays([1, 2, 3, 4], [5, 6, 7, 8]))
