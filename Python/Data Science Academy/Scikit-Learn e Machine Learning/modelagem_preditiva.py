# problema de negocio: e possivel prever o salario de alguem com base no tempo dedicado aos estudos em horas por mes

import pandas as pd, numpy as np, matplotlib.pyplot as plt, seaborn as sns
from sklearn.linear_model import LinearRegression
from sklearn.model_selection import train_test_split

df = pd.read_csv('arquivos/dataset5.csv')
print(df.head())

X = np.array(df['horas_estudo_mes']) # variavel preditora
X = X.reshape(-1,1) # reajusta o formato

y = df['salario'] # variavel alvo

X_treino, X_teste, y_treino, y_teste = train_test_split(X, y, test_size = 0.2, random_state = 42) # divisao dos dados em treinamento e teste

print(X_treino.shape)
print(X_teste.shape)
print(y_treino.shape)
print(y_teste.shape)

modelo = LinearRegression()

modelo.fit(X_treino, y_treino) # treina o algoritmo

plt.scatter(X, y, color = 'b', label = 'Dados Reais Historicos')
plt.plot(X, modelo.predict(X), color = 'r', label = 'Reta de Regressao com as Previsoes do Modelo')
plt.xlabel('Horas de Estudo')
plt.ylabel('Salario')
plt.legend()
plt.show()

score = modelo.score(X_teste, y_teste) # passa o parametro R^2
print(f"Coeficiente R^2: {score:.2f}")

print(modelo.intercept_) # w0 - interceptacao com o eixo y
print(modelo.coef_) # w1 - inclinacao da reta

# Deploy do modelo
horas_estudo_novo = np.array([[48]])
salario_previsto = modelo.predict(horas_estudo_novo)
print(f'Se voce estudar cerca de', horas_estudo_novo, 'horas por mes, seu salario pode ser igual a', salario_previsto)

#y_novo = w0 + w1 * X
#salario = modelo.intercept_ + (modelo.coef_ * horas_estudo_novo) # outro modo
#print(salario)                                                   #

horas_estudo_novo2 = np.array([[65]])
salario_previsto2 = modelo.predict(horas_estudo_novo2)
print(f'Se voce estudar cerca de', horas_estudo_novo2, 'horas por mes, seu salario pode ser igual a', salario_previsto2)

horas_estudo_novo3 = np.array([[73]])
salario_previsto3 = modelo.predict(horas_estudo_novo3)
print(f'Se voce estudar cerca de', horas_estudo_novo3, 'horas por mes, seu salario pode ser igual a', salario_previsto3)
