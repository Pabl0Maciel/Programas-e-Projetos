# pergunta de negocio: 'Existe alguma relacao entre a area de imoveis (m2) e o valor do aluguel em uma determinada cidade?

import statsmodels.api as sm, pandas as pd, matplotlib.pyplot as plt, seaborn as sns

df = pd.read_csv('arquivos/dataset4.csv')
print(df.head())

y = df['valor_aluguel'] # variavel dependente
X = df['area_m2'] # variavel independente
X = sm.add_constant(X) # adiciona uma constante a variavel independente

modelo = sm.OLS(y,X) # cria o modelo

resultado = modelo.fit() # treina o modelo

print(resultado.summary())

plt.figure(figsize = (12,8))
plt.xlabel('area_m2', size = 16)
plt.ylabel('valor_aluguel', size = 16)
plt.plot(X['area_m2'], y, 'o', label = 'Dados Reais')
plt.plot(X['area_m2'], resultado.fittedvalues, 'r-', label = 'Linha de Regressao (Previsao do Modelo)')
plt.legend(loc = 'best')

plt.show()

# conclusao: existe uma forte relacao entre o valor de alguel e a area, porem ainda existem mais variaveis que afetam o valor de alguel