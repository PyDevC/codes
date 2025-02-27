import atexit, io, sys

buffer = io.BytesIO()
sys.stdout = buffer

@atexit.register
def write():
    sys.stdout.write(buffer.getvalue())

x = input()
print(x)
x = int(input())
print(x)
x = list(map(int, input().split()))
print(x)
x = [int(x) for x in input().split()]
print(x)
