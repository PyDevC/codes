import inspect

"""inspect provides tools to get information about live objects in python.
These live objects include modules, classes, methods, functions, tracebacks,
frame objects, and code objects.

What are each of these things:
- modules: a module is a file that contains statments, functions, and other 
    python definitions which can be imported into other files using import 
    keyword.
- classes: classes are a way to bundle data and function together to provide
    easy access, better OOPS.
- methods: methods are functions that are part of a class or object or class.
- function: function are a group of statements that can be called anywhere in 
    the program in the scope.
- tracebacks: traceback is a module in python that handles the stack in the 
    python program such as functions, variables, etc.
- frame objects: Frames is the runtime structure that represents one level of 
    execution in the call stack. Each function call, module execution, or 
    generator context is associated with a frame that stores its execution 
    state.
- code objects: code objects are low-level details of CPython implementation.
    Each one represents a chunk of executable code that hasn't yet been bound 
    into a function.

There are four main kinds of services provided by this module: 
- type checking
- getting source code
- inspecting classes and functions
- examining the interpreter stack
"""

# Get members of Python Objects, classes or modules
print("object of object class")
a = object # Standard object type
a_out = inspect.getmembers(a) # it returns list of tuples so converted to dict
a_dict = dict(a_out)
for key, value in a_dict.items():
    print(key, value)

class B:
    def Print(self):
        print("This is a class")

print("=" * 80)
print("object of class B")
b = B()
b_out = inspect.getmembers(b)
b_dict = dict(b_out)
for key, value in b_dict.items():
    print(key, value)

print("=" * 80)
print("class B itself")
B_out = inspect.getmembers(B)
B_dict = dict(B_out)
for key, value in B_dict.items():
    print(key, value)

print("=" * 80)
print("Simple Empty function")
def myfunc():
    pass

myfunc_out = inspect.getmembers(myfunc)
myfunc_dict = dict(myfunc_out)
for key, value in myfunc_dict.items():
    print(key, value)
