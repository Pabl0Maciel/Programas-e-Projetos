import pandas as pd
from pandas import DataFrame

dados = {'Estado': ['Santa Catarina', 'Rio de Janeiro', 'Tocantins', 'Bahia', 'Minas Gerais'],
         'Ano': [2004, 2005, 2006, 2007, 2008],
         'Taxa Desemprego': [1.5, 1.7, 1.6, 2.4, 2.7],
         'Taxa Crescimento': [0.0, 1.0, 2.0, 3.0, 4.0]}

df = DataFrame(dados, index = ['estado1', 'estado2', 'estado3', 'estado4', 'estado5'])
print(df)
print(df['estado2' : 'estado4']) # neste caso nao e exclusivo, retorna a linha 4
print(df[df['Taxa Desemprego'] < 2]) # retorna as linhas onde a taxa desemprego e menor que 2