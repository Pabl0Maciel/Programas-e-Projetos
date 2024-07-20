import matplotlib.pyplot as plt, numpy as np

n = np.random.randn(100000)

fig, axes = plt.subplots(1, 2, figsize = (12,4))

# plot 1
axes[0].hist(n) # cria um histograma com os valores de n no eixo 
axes[0].set_title('Histograma padrao')
axes[0].set_xlim(min(n), max(n)) # calcula os extremos de n e os define como limite do eixo x

# plot 2
axes[1].hist(n, cumulative = True, bins = 50)
axes[1].set_title('Histograma cumulativo')
axes[1].set_xlim(min(n), max(n))

plt.show()


