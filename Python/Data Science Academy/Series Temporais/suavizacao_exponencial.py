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

# Suavizacao Exponencial
modelo = SimpleExpSmoothing(serie_temporal) # cria o modelo

modelo_ajustado = modelo.fit(smoothing_level = 0.2) # treina (ajusta) o modelo

suavizacao_exponencial = modelo_ajustado.fittedvalues # extrai os valores previstos

# grafico
plt.figure(figsize = (12,6))
plt.plot(serie_temporal, label = 'Valores Reais') # plota o grafico com os valores reais
plt.plot(suavizacao_exponencial, label = 'Valores Previstos', linestyle = '--') # plota o grafico com valores previstos
plt.xlabel('Data')
plt.ylabel('Vendas')
plt.title('Modelo de Suavizacao Exponencial')
plt.legend()

plt.show()

# Deploy e Previsao
num_previsoes = 1 # previsao para o proximo dia
previsoes = modelo_ajustado.forecast(steps = num_previsoes) # calcula a previsao para o dia passado

print('Previsao do Total de Vendas Para Janeiro de 2024:', round(previsoes[0], 4))