import matplotlib.pyplot as plt, numpy as np, matplotlib as mpl
from mpl_toolkits.mplot3d.axes3d import Axes3D

# dados
alpha = 0.7 # transparencia
phi_ext = 2 * np.pi * 0.5

def ColorMap(phi_m, phi_p): # funcao para o mapa de cores
    return( + alpha - 2 * np.cos(phi_p) * np.cos(phi_m) - alpha * np.cos(phi_ext - 2 * phi_p))

phi_m = np.linspace(0, 2*np.pi, 100)
phi_p = np.linspace(0, 2*np.pi, 100)
x, y = np.meshgrid(phi_p, phi_m)
z = ColorMap(x, y).T

# criando figura
fig = plt.figure(figsize = (14,6))

### subplot 1 com projecao 3d
ax = fig.add_subplot(1, 2, 1, projection = '3d')
p = ax.plot_surface(x, y, z, rstride = 4, cstride = 4, linewidth = 0)

### subplot 2 com projecao 3d
ax = fig.add_subplot(1, 2, 2, projection = '3d')
p = ax.plot_surface(x, y, z, rstride = 1, cstride = 1, cmap = mpl.cm.coolwarm, linewidth = 0, antialiased = False )

cb = fig.colorbar(p, shrink = 0.5) # cria a barra de cores como legenda

# wire frame
fig2 = plt.figure(figsize = (8,6))

ax2 = fig2.add_subplot(1, 1, 1, projection = '3d')
p2 = ax2.plot_wireframe(x, y, z, rstride = 4, cstride = 4)

plt.show()
