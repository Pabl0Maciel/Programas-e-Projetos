import pandas as pd

# preenchendo valores ausentes
df = pd.read_csv("arquivos/dataset2.csv") # importa arquivo csv
print(df.head(3)) # retorna as 3 primeiras linhas (retorna 5 por padrao)
print(df.isna().sum()) # soma a quantidade de valores ausentes de cada coluna

moda = df['Quantidade'].value_counts().index[0] # calcula a moda
print(moda) 

df['Quantidade'].fillna(value = moda, inplace = True) # preenche os valores ausentes com a moda
print(df.head()) 

# realizando uma query (consulta)
print(df.Valor_Venda.describe())

df2 = df.query('229 < Valor_Venda < 10000') # busca as linhas da coluna dos valores de venda que estao entre 229 e 10000
print(df2.Valor_Venda.describe())

df3 = df2.query('Valor_Venda > 766')
print(df3.head())