# problema de negocio: e possivel prever o salario de alguem com base no tempo dedicado aos estudos em horas por mes

import pandas as pd, numpy as np, matplotlib.pyplot as plt, seaborn as sns
from sklearn.linear_model import LinearRegression
from sklearn.model_selection import train_test_split

df = pd.read_csv('arquivos/dataset5.csv')
print(df.head())
#print(df.isnull().sum())

print(df.corr()) # mostra a correlacao
print(df.describe())

sns.histplot(data = df, x = 'horas_estudo_mes', kde = True)


X = np.array(df['horas_estudo_mes']) # variavel preditora
X = X.reshape(-1,1) # reajusta o formato

y = df['salario'] # variavel alvo

plt.figure()
plt.scatter(X, y, color = 'b', label = 'Dados Reais Historicos')
plt.xlabel('Horas de Estudo')
plt.ylabel('Salario')
plt.legend()

plt.show()