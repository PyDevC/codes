from sys import stdin, stdout

s = stdin.readline().split(",")
s = sorted(s)

stdout.write(",".join(s))
