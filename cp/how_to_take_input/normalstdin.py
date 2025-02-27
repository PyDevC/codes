from sys import stdin, stdout

x = stdin.readline()
stdout.write(str(x))

x = int(stdin.readline())
print(x)
x = list(map(int, stdin.readline().split()))
print(x)
x = [int(x) for x in stdin.readline().split()]
print(x)
x = list(map(int, stdin.readline().strip().split()))
print(x)
