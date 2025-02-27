from sys import stdin, stdout

x = [int(x) for x in stdin.readline().split(",")]
stdout.write(str(x)+ "\n")
x = tuple(x)
stdout.write(str(x)+ "\n")
