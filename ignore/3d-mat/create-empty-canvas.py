from mpl_toolkits import mplot3d
import numpy as np
import matplotlib.pyplot as plt

fig = plt.figure()
ax = plt.axes(projection="3d")

x,y,z = mplot3d.axes3d.get_test_data(0.07)
ax.contour(x,y,z)

plt.show()
