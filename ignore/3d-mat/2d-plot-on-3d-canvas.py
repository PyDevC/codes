import matplotlib.pyplot as plt
import numpy as np

x = np.arange(0, 1, 0.1)
y = np.arange(0, 1, 0.1)
z = np.zeros_like(x)

#x = x * np.cos 
#y = y * np.cos 

fig = plt.figure()
ax = plt.axes(projection='3d')

ax.scatter(x, y, zs=0)
ax.set_xlim(0,1)
ax.set_ylim(0,1)
ax.set_zlim(0,1)

plt.show()
