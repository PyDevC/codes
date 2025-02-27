from sys import stdin, stdout, setrecursionlimit
import sys
setrecursionlimit(10000000)
sys.set_int_max_str_digits(1000000)

# oneliner
def f(n): return 1 if n<2 else n*f(n-1)

#stdout.write(str(f(int(stdin.readline()))))

# Split recursive
def split_re(n):
    a, b, i = 1, 2, 2
    while i < n:
        c = a*b
        i += 1
        a, b = c, i
    return  a*b if n > 1 else 1

#stdout.write(str(split_re(int(stdin.readline()))))

# builtin
from math import factorial
stdout.write(str(factorial(int(stdin.readline())))) # fastest
