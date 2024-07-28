import pandas as pd

dados = {'Estado': ['Santa Catarina', 'Rio de Janeiro', 'Tocantins', 'Bahia', 'Minas Gerais'],
         'Ano': [2004, 2005, 2006, 2007, 2008],
         'Taxa Desemprego': [1.5, 1.7, 1.6, 2.4, 2.7]}

print(dados)

from pandas import DataFrame

df = DataFrame(dados) # transforma o dicionario em uma tabela
print(df.head()) # mostra as 5 primeiras linhas da tabela
print(type(df))

df2 = DataFrame(dados, columns = ['Estado', 'Taxa Desemprego', 'Ano']) # reorganiza as colunas
print(df2.head())

df3 = DataFrame(dados,                                                              # cria um dataframe e
                columns = ['Estado', 'Taxa Desemprego', 'Taxa Crescimento', 'Ano'], # acrescenta mais uma coluna
                index = ['estado1', 'estado2', 'estado3', 'estado4', 'estado5'])    # e tambem o indice
print(df3.head())
print(df3.columns) # mostra as colunas
print(df3.values) # mostra os valores
print(df3.dtypes) # mostra os tipos das colunas
print(df3['Estado']) # imprime uma coluna
print(df3[['Taxa Desemprego', 'Ano']]) # imprime duas colunas
print(df3.index) # retorna os indices
print(df3.filter(items = ['estado3'], axis = 0)) # filtra a linha do indice
