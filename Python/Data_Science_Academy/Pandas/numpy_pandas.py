import pandas as pd
from pandas import DataFrame

dados = {'Estado': ['Santa Catarina', 'Rio de Janeiro', 'Tocantins', 'Bahia', 'Minas Gerais'],
         'Ano': [2004, 2005, 2006, 2007, 2008],
         'Taxa Desemprego': [1.5, 1.7, 1.6, 2.4, 2.7]}

df = DataFrame(dados,                                                              
                columns = ['Estado', 'Taxa Desemprego', 'Taxa Crescimento', 'Ano'],
                index = ['estado1', 'estado2', 'estado3', 'estado4', 'estado5'])

print(df.describe()) # faz o resumo estatistico dos dados numericos
print(df.isna()) # retorna True onde tem valor ausente

import numpy as np
df['Taxa Crescimento'] = np.arange(5.) # preenche a coluna com valores de 0.0 a 4.0
print(df)
print(df.describe())

