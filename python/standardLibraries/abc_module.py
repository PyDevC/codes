import abc
# Look into pep:3119
# Look into pep:3141
import collections.abc as collabc
from abc import ABC, ABCMeta, abstractmethod

def collect():
    pass

if isinstance(collect, collabc.Callable):
    print("collect is callable")
