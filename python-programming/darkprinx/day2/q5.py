from sys import stdin, stdout


class string:

    def __init__(self):
        self.s = None

    def getString(self):
        self.s = stdin.readline()

    def printString(self):
        stdout.write(str(self.s))


n = string()
n.getString()
n.printString()
