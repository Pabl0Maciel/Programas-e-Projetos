import pandas as pd

df = pd.read_csv("arquivos/dataset2.csv") 
moda = df['Quantidade'].value_counts().index[0] 
df['Quantidade'].fillna(value = moda, inplace = True) 

print(df[['Segmento', 'Regiao', 'Valor_Venda']].groupby(['Segmento', 'Regiao']).mean()) # escolhe as colunas de segmento, regiao e valor_venda. Agrupa as     
                                                                                        # colunas de segmento e regiao. Por fim, calcula a media da coluna 
                                                                                        # nao agrupada (valor_venda)

print(df[['Segmento', 'Regiao', 'Valor_Venda']].groupby(['Segmento', 'Regiao']).agg(['mean', 'std', 'count'])) # calcula a media, desvio padrao e contagem