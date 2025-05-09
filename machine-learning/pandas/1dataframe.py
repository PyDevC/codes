import pandas as pd
from collections.abc import Iterable
 
# learn how to create a pandas dataframe using different methods
# DataFrame is a class that takes in various inputs to create a dataframe
# it takes in input as ndarray, iterable, dict, or another dataframe

# from an iterable such as list
df = pd.DataFrame([1, 2, 2, 3, 4, 4])
print(df)

