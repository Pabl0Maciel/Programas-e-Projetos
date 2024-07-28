import matplotlib.pyplot as plt, numpy as np

x = np.linspace(0, 5, 10)
y = x ** 2

# diferentes escalas
fig, axes = plt.subplots(1, 2, figsize = (10, 4))

### grafico 1
axes[0].plot(x, x**2, x, np.exp(x))
axes[0].set_title('Escala Padrao')

### grafico 2
axes[1].plot(x, x**2, x, np.exp(x))
axes[1].set_yscale('log') # altera a escala para logaritmca
axes[1].set_title('Escala logaritmca (y)')

# com grid
fig2, axes2 = plt.subplots(1, 2, figsize = (10, 3))

### grafico 1
axes2[0].plot(x, x**2, x, x**3, lw = 2)
axes2[0].grid(True) # cria o grid padrao

### grafico 2
axes2[1].plot(x, x**2, x, x**3, lw = 2)
axes2[1].grid(color = 'b', alpha = 0.7, linestyle = 'dashed', linewidth = 0.8) # customiza o grid

# diferentes estilos em uma mesma figura
xx =np.linspace(-0.75, 1., 100)
n = np.array([0,1,2,3,4,5])

fig3, axes3 = plt.subplots(1, 4, figsize = (12,3))

### plot 1
axes3[0].scatter(xx, xx + 0.25 * np.random.randn(len(xx)), color = 'k')
axes3[0].set_title('Scatter')

### plot 2
axes3[1].step(n, n ** 2, lw = 2, color = 'b')
axes3[1].set_title('step')

### plot 3
axes3[2].bar(n, n ** 2, align = 'center', width = 0.5, alpha = 0.5, color = 'm')
axes3[2].set_title('barras')

### plot 4
axes3[3].fill_between(x, x ** 2, x ** 3, alpha = 0.5, color = 'g')
axes3[3].set_title('fill_between')

plt.show()