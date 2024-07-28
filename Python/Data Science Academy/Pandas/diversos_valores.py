import pandas as pd

df = pd.read_csv("arquivos/dataset2.csv") 
moda = df['Quantidade'].value_counts().index[0] 
df['Quantidade'].fillna(value = moda, inplace = True) 

print(df.shape) # retorna '(linhas, colunas)'

print(df[df['Quantidade'].isin([5,7,9,11])]) # aplica um filtro que procura as linhas em que as qntds passadas estao presentes

print(df[df['Quantidade'].isin([5,7,9,11])].shape) # retorna o numero de linhas e colunas apos o filtro

print(df[df['Quantidade'].isin([5,7,9,11])][:10]) # aplica o filtro ate a linha 10