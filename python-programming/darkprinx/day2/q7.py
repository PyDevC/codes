from sys import stdin, stdout

x, y = map(int, stdin.readline().split())

arr = [[i for i in range(x)] for j in range(y)]

stdout.write(str(arr))
