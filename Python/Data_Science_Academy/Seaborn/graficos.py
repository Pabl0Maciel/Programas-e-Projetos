import seaborn as sea, random, numpy as np, pandas as pd, matplotlib as mat, matplotlib.pyplot as plt, warnings

warnings.filterwarnings('ignore')

dados = sea.load_dataset('tips') # importa dataset
#print(dados.head())

sea.jointplot(data = dados, x = 'total_bill', y = 'tip', kind = 'reg') # cria uma figura com varios graficos relacionando o total_bill e as tips

sea.lmplot(data = dados, x = 'total_bill', y = 'tip', col= 'smoker') # cria dois graficos, um com fumantes e outro com nao fumantes

# criando dataframe
df = pd.DataFrame()
df['idade'] = random.sample(range(20, 100), 30)
df['peso'] = random.sample(range(55, 150), 30)
print(df.shape)
print(df.head())

# transformando em grafico
sea.lmplot(data = df, x = 'idade', y = 'peso', fit_reg = True) # grafico com modelo de regressao

plt.figure()
sea.kdeplot(df.idade) # grafico de densidade

plt.figure()
sea.kdeplot(df.peso) # grafico de densidade

plt.figure()
sea.distplot(df.peso) # histograma + grafico de densidade

plt.figure()
plt.hist(df.idade, alpha = 0.3) # usa o matplot para criar um histograma
sea.rugplot(df.idade) # coloca rugas no histograma criado para localizar as idades exatas

plt.figure()
sea.boxplot(df.idade, color = 'm') # cria um boxplot

plt.figure()
sea.boxplot(df.peso, color = 'y') # cria um boxplot

plt.figure()
sea.violinplot(df.idade, color = 'g') # cria um grafico na forma de violao

plt.figure()
sea.violinplot(df.peso, color = 'cyan') # cria um grafico na forma de violao

sea.clustermap(df)


plt.show()