import sys

for i in range(2000, 3201):
    if (i % 7 == 0) and (i % 5 != 0):
        sys.stdout.write(str(i) + ",")
sys.stdout.write("\b")
