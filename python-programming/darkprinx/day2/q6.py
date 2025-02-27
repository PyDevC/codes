from sys import stdin, stdout
from math import sqrt

d = list(map(int, stdin.readline().strip().split(",")))
c = 50
h = 30

x = [str(int(sqrt(2*c*float(i)/h))) for i in d]
stdout.write(str(x))
