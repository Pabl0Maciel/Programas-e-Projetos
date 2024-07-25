# Problema de Negocio: usando dados historicos ao longo de 2023, seria possivel prever o total de vendas em janeiro de 2024

import pandas as pd, numpy as np, matplotlib.pyplot as plt, seaborn as sns
from statsmodels.tsa.holtwinters import SimpleExpSmoothing

df = pd.read_csv('arquivos/dataset6.csv')
print(df.head())


# Pre-Processamento
print(df['Data'].min())
print(df['Data'].max())
print(df.info())

df['Data'] = pd.to_datetime(df['Data']) # converte para o tipo datetime
print(df.info())

serie_temporal = df.set_index('Data')['Total_Vendas'] # converte a coluna Data para indice
print(type(serie_temporal))

serie_temporal = serie_temporal.asfreq('D') # configura a frequencia como diaria

# grafico
plt.figure(figsize = (12,6))
plt.plot(serie_temporal, color = 'white', linewidth = 2) # cria o grafico

plt.gca().set_facecolor('#2e03a3') # configura a cor
plt.grid(color = 'yellow', linestyle = '--', linewidth = 0.5) # configura o estilo

plt.xlabel('Data', color = 'k', fontsize = 14) # legenda ao eixo X
plt.ylabel('Vendas', color ='k', fontsize = 14) # legenda ao eixo Y
plt.title('Serie Temporal de Vendas', color = 'k', fontsize = 18)

plt.tick_params(axis = 'x', colors = 'k')
plt.tick_params(axis = 'y', colors = 'k')

plt.show()
