# pergunta de negocio: 'Existe alguma relacao entre a area de imoveis (m2) e o valor do aluguel em uma determinada cidade?

import statsmodels.api as sm, pandas as pd, matplotlib.pyplot as plt, seaborn as sns

df = pd.read_csv('arquivos/dataset4.csv')
print(df.head())

#print(df.isnull().sum()) # verifica se possui valores ausentes
print(df['valor_aluguel'].describe()) # resumo da variavel alvo

sns.histplot(data = df, x = 'valor_aluguel', kde = True) # histograma

df.corr() # exibe um tabela de correlacao entre as variaveis (-1 indica uma correlacao indireta, 0 indica que nao ha correlacao e 1 indicar correlaco direta)

plt.figure()
sns.scatterplot(data = df, x= 'area_m2', y = 'valor_aluguel') # grafico de dispensao

plt.show()