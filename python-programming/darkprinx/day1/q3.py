from sys import stdin, stdout

nums = [int(x) for x in stdin.readline().split()]
x = {key: value for key, value in zip(nums, list(map(lambda i: i**2, nums)))}
stdout.write(str(x))
