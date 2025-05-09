import matplotlib.pyplot as plt
from matplotlib import cm
import numpy as np

fig = plt.figure()
ax = plt.axes(projection='3d')

_x = np.linspace(1,100)
_y = np.linspace(1,100)

x,y = np.meshgrid(_x,_y)
x = np.cos(np.pi * x)
y = np.sin(np.pi * y)
print(x.size, y.size)
z = np.tan(np.pi*x) *  np.cos(np.pi*y)
print(z.size)

ax.plot_wireframe(x,y,z, cmap=cm.coolwarm)

plt.show()
