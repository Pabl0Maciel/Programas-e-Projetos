import matplotlib.pyplot as plt

# grafico de linhas
plt.figure()
plt.plot([1, 3, 5], [2, 4, 7]) # cria o grafico (eixo x e a primeira lista e y a segunda)

###
plt.figure()
x = [2, 3, 5]
y = [3, 5, 7]
plt.plot(x,y)
plt.xlabel ('Variavel 1') # legenda ao eixo x
plt.ylabel('Variavel 2') # legenda ao eixo y
plt.title('Teste Plot') # titulo do grafico

###
plt.figure()
x2 = [1, 2, 3]
y2 = [11, 12, 15]
plt.plot(x2, y2, label = 'Grafico com Matplotlib') # cria um grafico de linhas com legenda na linha
plt.legend() # adiciona a legenda ao grafico

# grafico de barras
plt.figure()
x3 = [2, 4, 6, 8, 10]
y3 = [6, 7, 8, 2, 4]
plt.bar(x3, y3, label = 'Barras', color = 'green') # cria um grafico de barras com legenda 'barras' e cor verde
plt.legend()

###
plt.figure()
x4 = [1, 3, 5, 7, 9]
y4 = [7, 8, 2, 4, 2]
plt.bar(x3, y3, label = 'Listas 1', color = 'blue') # cria o grafico de barras
plt.bar(x4, y4, label = 'Listas2', color = 'red') # cria o grafico de barras (como plt.bar foi chamado duas vezes, os graficos estarao na mesma figura)
plt.legend()

###
plt.figure()
idades = [22, 65, 45, 55, 21, 22, 34, 42, 41, 4, 99, 101, 120, 122, 130, 111, 115, 80, 75, 54, 44, 64, 13, 18, 48]
ids = [x for x in range(len(idades))] # retorna os indices
print(ids)
plt.bar(ids, idades)

###
plt.figure()
bins = [0, 10, 20, 30, 40, 50, 60, 70, 80, 90, 100, 110, 120, 130] # cria as faixas etarias (0-10 anos, 10-20 anos, ...)
plt.hist(idades, bins, histtype = 'bar', rwidth = 0.8) # cria um histograma do tipo barra

###
plt.figure()
plt.hist(idades, bins, histtype = 'stepfilled', rwidth = 0.8) # cria o mesmo grafico mas com os espacos preenchidos

plt.show()

