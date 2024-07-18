import pandas as pd

df = pd.read_csv("arquivos/dataset2.csv") 
moda = df['Quantidade'].value_counts().index[0] 
df['Quantidade'].fillna(value = moda, inplace = True) 

print(df[(df.Segmento == 'Home Office') & (df.Regiao == 'South')].head()) # filtra as vendas que ocorreram para o segmento home office E na regiao south

print(df[(df.Segmento == 'Home Office') | (df.Regiao == 'South')].tail()) # filtra as vendas que ocorreram para o segmento home office OU na regiao south (tail = cauda/final)

print(df[(df.Segmento != 'Home Office') & (df.Regiao != 'South')].sample(5)) # filtra as vendas que NAO ocorreram para o segmento home office E NEM na regiao south (sample = amostra aleatoria)
