import matplotlib.pyplot as plt, numpy as np

# criando grafico do zero
x = np.linspace(0, 5, 10) # cria uma lista de 10 numeros espacados igualmente na razao de 5
print(x)
y = x ** 2

fig = plt.figure()
axes = fig.add_axes([0.1, 0.1, 0.8, 0.8]) # cria os eixos

axes.plot(x, y, 'r') # cria o grafico

axes.set_xlabel('x') # coloca a legenda do eixo x
axes.set_ylabel('y') # coloca a legenda do eixo y
axes.set_title('Grafico de linha') # coloca o titulo

# duas figuras de grafico juntas
fig2 = plt.figure()

axes1 = fig2.add_axes([0.1, 0.1, 0.8, 0.8])
axes2 = fig2.add_axes([0.2, 0.5, 0.4, 0.3])

### grafico principal
axes1.plot(x, y, 'r') 
axes1.set_xlabel('x') 
axes1.set_ylabel('y') 
axes1.set_title('Grafico principal') 

### grafico secundario
axes2.plot(y, x, 'g') # inversao dos dados (x,y -> y,x)
axes2.set_xlabel('y') 
axes2.set_ylabel('x') 
axes2.set_title('Grafico secundario') 

# graficos em pararelo
fig3, axes3 = plt.subplots(nrows = 1, ncols = 2) # cria uma figura com uma linha e duas colunas de subplots e retorna uma lista de eixos (axes3) que pode 
                                                 # ser iterada

for ax in axes3:
    ax.plot(x, y, 'r') 
    ax.set_xlabel('x') 
    ax.set_ylabel('y') 
    ax.set_title('Titulo') 
fig3.tight_layout()

plt.show()

