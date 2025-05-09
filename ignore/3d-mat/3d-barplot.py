import matplotlib.pyplot as plt
import numpy as np

x = np.random.randint(1,100, 10)
y = np.random.randint(1,100, 10)

fig = plt.figure()
ax = plt.axes(projection='3d')

x, y = np.meshgrid(x,y)
x, y = x.ravel(), y.ravel()

ax.bar3d(x,y, 1, 10, 10, 1, shade=True)

plt.show()
